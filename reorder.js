const fs = require("fs");

const filePath = "Shared/Entity.h";

function shuffleArray(array)
{
    for (let i = array.length - 1; i > 0; i--)
    {
        const j = Math.floor(Math.random() * (i + 1));
        [array[i], array[j]] = [array[j], array[i]];
    }
    return array;
}

function modify_component_list(data)
{
    const raw_lines = data.split('\n');
    const unmodded_lines = [];
    const target_lines = [];
    const parsed_names = [];
    const parsed_ids = [];
    let pushing = false;
    for (let i = 0; i < raw_lines.length; i++)
    {
        if (pushing)
            target_lines.push(raw_lines[i]);
        else
            unmodded_lines.push(raw_lines[i]);
        if (raw_lines[i].startsWith("#define RR_FOR_EACH_COMPONENT"))
            pushing = true;
    }

    for (let i = 0; i < target_lines.length; i++)
    {
        parsed_names.push(target_lines[i].slice(target_lines[i].indexOf("(") + 1, target_lines[i].indexOf(",")));
        parsed_ids.push(target_lines[i].slice(target_lines[i].indexOf(", ") + 2, target_lines[i].indexOf(")")));
    }

    shuffleArray(parsed_names);
    shuffleArray(parsed_ids);
    // builder
    let new_file = unmodded_lines.join("\n");
    for (let i = 0; i < target_lines.length; i++)
        new_file += `\n    XX(${parsed_names[i]}, ${parsed_ids[i]}) \\`

    return new_file.substring(0, new_file.length - 1);
}

function field_list_modify_enum(data)
{
    const raw_lines = data.split("\n");
    const lines_before = [];
    const target_lines = [];
    const lines_after = [];
    let ever_hit_target = false;
    let within_target = false;
    for (let i = 0; i < raw_lines.length; i++)
    {
        const line = raw_lines[i];
        if (line.includes("_all = "))
            within_target = false;
        if (!ever_hit_target)
            lines_before.push(line);
        if (ever_hit_target && !within_target)
            lines_after.push(line);
        if (within_target)
            target_lines.push(line);
        if (!ever_hit_target && line == "{")
        {
            ever_hit_target = true;
            within_target = true;
        }
    }

    const target_names = [];
    const target_enum_values = [];
    for (let i = 0; i < target_lines.length; i++)
    {
        let name = target_lines[i];
        name = name.trim();
        const equals = name.indexOf(" =");
        target_names.push(name.slice(0, equals));
        let value = name.slice(equals + 3, name.length - 1);
        target_enum_values.push(value)
    }

    shuffleArray(target_names);

    // build
    const builder_target = [];
    for (let i = 0; i < target_names.length; i++)
        builder_target[i] = `\n    ${target_names[i]} = ${target_enum_values[i]},`;
    let new_file = lines_before.join("\n");
    new_file += builder_target.join("") + "\n";
    new_file += lines_after.join("\n");

    return new_file;
}

function field_list_modify_fields(data)
{
    const raw_lines = data.split("\n");
    const lines_before = [];
    let target_lines = [];
    const lines_after = [];
    let within_target = false;
    let ever_hit_target = false;

    for (let i = 0; i < raw_lines.length; i++)
    {
        const line = raw_lines[i];
        if (line == "")
            within_target = false;    
        if (within_target)
            target_lines.push(line);
        if (!ever_hit_target)
            lines_before.push(line);
        if (ever_hit_target && !within_target)
            lines_after.push(line);
        if (line == "#define FOR_EACH_PUBLIC_FIELD \\")
        {
            within_target = true;
            ever_hit_target = true;
        }
    }

    target_lines = target_lines.map((x, i, a) => {
        if (x.endsWith("\\"))
            x = x.substring(0, x.length - 1);
        return `    ${x.trim()} \\`;
    });

    shuffleArray(target_lines);

    let target_lines_str = target_lines.join("\n");
    target_lines_str = target_lines_str.substring(0, target_lines_str.length - 1);

    let new_file = lines_before.join("\n");
    new_file += "\n" + target_lines_str + "\n";
    new_file += lines_after.join("\n");

    return new_file;
}

function modify_field_list(data)
{
    return field_list_modify_enum(field_list_modify_fields(data));
}

function modify_file(name, cb)
{
    name = __dirname + name;
    let data = fs.readFileSync(name, "utf8");
    data = cb(data);
    fs.writeFileSync(name, data, "utf8");
}

modify_file("/Shared/Entity.h", modify_component_list);
modify_file("/Shared/Component/Arena.c", modify_field_list);
modify_file("/Shared/Component/Drop.c", modify_field_list);
modify_file("/Shared/Component/Flower.c", modify_field_list);
modify_file("/Shared/Component/Health.c", modify_field_list);
modify_file("/Shared/Component/Mob.c", modify_field_list);
modify_file("/Shared/Component/Petal.c", modify_field_list);
modify_file("/Shared/Component/Physical.c", modify_field_list);
modify_file("/Shared/Component/PlayerInfo.c", modify_field_list);
modify_file("/Shared/Component/Relations.c", modify_field_list);
