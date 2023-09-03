const parse_path = (path, x, y) => {
    let at = 0;
    path = path.replaceAll(/[a-z]/g, str => ' ' + str + ' ');
    path = path.slice(1, path.length - 1).split(' ').filter(x => x);
    let ret_str = 'rr_renderer_begin_path(renderer);\n';
    let curr_op = 'm';
    const op_parse = _ => {
        switch(curr_op)
        {
            case 'm':
                x += parseFloat(path[at++]);
                y += parseFloat(path[at++]);
                ret_str += `rr_renderer_move_to(renderer, ${x.toFixed(2)}, ${y.toFixed(2)});\n`;
                break;
            case 'l':
            {
                const prev_x = x;
                const prev_y = y;
                x += parseFloat(path[at++]);
                y += parseFloat(path[at++]);
                if (Math.abs(x - prev_x) > 0.001 || Math.abs(y - prev_y) > 0.001)
                    ret_str += `rr_renderer_line_to(renderer, ${x.toFixed(2)}, ${y.toFixed(2)});\n`;
                break;
            }
            case 'q':
            {
                const x1 = x + parseFloat(path[at++]);
                const y1 = y + parseFloat(path[at++]);
                x += parseFloat(path[at++]);
                y += parseFloat(path[at++]);
                ret_str += `rr_renderer_quadratic_curve_to(renderer, ${x1.toFixed(2)}, ${y1.toFixed(2)}, ${x.toFixed(2)}, ${y.toFixed(2)});\n`;
                break;
            }
            case 'c':
            {
                const x1 = x + parseFloat(path[at++]);
                const y1 = y + parseFloat(path[at++]);
                const x2 = x + parseFloat(path[at++]);
                const y2 = y + parseFloat(path[at++]);
                x += parseFloat(path[at++]);
                y += parseFloat(path[at++]);
                ret_str += `rr_renderer_bezier_curve_to(renderer, ${x1.toFixed(2)}, ${y1.toFixed(2)}, ${x2.toFixed(2)}, ${y2.toFixed(2)}, ${x.toFixed(2)}, ${y.toFixed(2)});\n`;
                break;
            }
            case 'z':
                break;
        }
    }
    while (at < path.length)
    {
        if (!Number.isFinite(parseFloat[path[at]]))    
            curr_op = path[at++];
        op_parse();
    }
    return ret_str;
}

const parse_svg = str => {
    let doc = new DOMParser().parseFromString(str, 'text/xml');
    const [offset_x, offset_y] = doc.getElementsByTagName('svg')[0].attributes.viewBox.value.split(' ').map(x => parseFloat(x)).slice(2);
    doc = [...doc.getElementsByTagName('path')].map(x => x.attributes).filter(x => !x["clip-rule"] && (!x["fill-opacity"] || parseFloat(x["fill-opacity"].nodeValue) !== 0));
    let ret = "";
    for (let x of doc)
    {
        if (x["fill"])
        {
            if (x["fill-opacity"])
                ret += `rr_renderer_set_fill(renderer, 0x${((x["fill-opacity"].nodeValue * 255) | 0).toString(16).padStart(2, '0')}${x["fill"].nodeValue.slice(1)});\n`;
            else
                ret += `rr_renderer_set_fill(renderer, 0xff${x["fill"].nodeValue.slice(1)});\n`;
        }
        ret += parse_path(x["d"].nodeValue, -offset_x / 2, -offset_y / 2);
        if (x["fill"])
            ret += `rr_renderer_fill(renderer);\n`;
    }
    console.log(ret);
}