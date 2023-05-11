namespace app
{
    bool IsSafeJson(std::string const &json)
    {
        for (uint64_t i = 0; i < json.size(); i++)
        {
            std::string::value_type a = json[i];
            if (a == '\n')
                return false;
            if (a == '\x00')
                return false;
            if (a == '\"')
                return false;
            if (a == '\'')
                return false;
            if (a == '\\')
                return false;
        }

        return true;
    }    
}
