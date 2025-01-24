#pragma once

class SteamProfileXMLParser
{
public:
    SteamProfileXMLParser(std::uint64_t steamid64) {
        std::string steam_profile_url = "https://steamcommunity.com/profiles/";
        steam_profile_url.append(std::to_string(steamid64)), steam_profile_url.append("/?xml=1");

        CURL* curl_handle;

        curl_global_init(CURL_GLOBAL_ALL);
        curl_handle = curl_easy_init();

        curl_easy_setopt(curl_handle, CURLOPT_URL, steam_profile_url.c_str());
        curl_easy_setopt(curl_handle, CURLOPT_FOLLOWLOCATION, 1);
        curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L);
        curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, this->curl_writecallbackfn);
        curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &this->raw_xml_data);

        curl_easy_perform(curl_handle);
        curl_easy_cleanup(curl_handle);
    }

    /* TODO: do some cleanup and error handling */
    bool parse() {
        std::string raw_xml_data_cpy = this->raw_xml_data;

        /* deletes specified data tags (add tags in this function you want deleted) */
        this->create_delimeters();

        std::string::size_type topline_first = raw_xml_data_cpy.find_first_of("<?xml");
        std::string::size_type topline_last = raw_xml_data_cpy.find("<profile>", topline_first);

        if (topline_first != std::string::npos && topline_last != std::string::npos)
            raw_xml_data_cpy.erase(topline_first, (topline_last - topline_first) + std::string("<profile>").length());

        /* delete from <customURL> tag and down, as some of it is unhandled, this is for you todo */
        std::string::size_type delete_sub_sections = raw_xml_data_cpy.find("<customURL>");
        if (delete_sub_sections != std::string::npos)
            raw_xml_data_cpy.erase(delete_sub_sections, raw_xml_data_cpy.length());

        if (this->delimeters.size() >= 1) {
            for (int i = 0; i <= this->delimeters.size() - 1; i++) {
                std::string::size_type first = raw_xml_data_cpy.find(this->delimeters.at(i).first);
                std::string::size_type last = raw_xml_data_cpy.find(this->delimeters.at(i).second, first);

                if (first != std::string::npos && last != std::string::npos)
                    raw_xml_data_cpy.erase(first, (last - first) + this->delimeters.at(i).second.length());
            }
        }

        size_t cdata_begin_pos, cdata_end_pos = std::string::npos;
        std::string cdata_begin = "<![CDATA[", cdata_end = "]]>";

        while ((cdata_begin_pos = raw_xml_data_cpy.find(cdata_begin)) != std::string::npos) {
            raw_xml_data_cpy.erase(cdata_begin_pos, cdata_begin.length());
        }

        while ((cdata_end_pos = raw_xml_data_cpy.find(cdata_end)) != std::string::npos) {
            raw_xml_data_cpy.erase(cdata_end_pos, cdata_end.length());
        }

        std::string::size_type bottomline_profile = raw_xml_data_cpy.find("</profile>");
        if (bottomline_profile != std::string::npos)
            raw_xml_data_cpy.erase(bottomline_profile, std::string("</profile>").length());

        raw_xml_data_cpy.erase(std::remove(raw_xml_data_cpy.begin(), raw_xml_data_cpy.end(), '\t'), raw_xml_data_cpy.end());
        raw_xml_data_cpy.erase(std::remove(raw_xml_data_cpy.begin(), raw_xml_data_cpy.end(), '\r'), raw_xml_data_cpy.end());

        std::vector<std::string> lines;
        std::string::size_type last_newline_pos = { }, newline_pos = { };

        std::string::size_type first_empty_line = raw_xml_data_cpy.find('\n');
        if (first_empty_line != std::string::npos)
            raw_xml_data_cpy.erase(first_empty_line, first_empty_line + 1);

        std::string raw_xml_data_second_cpy = raw_xml_data_cpy;
        while ((newline_pos = raw_xml_data_second_cpy.find_first_of("\n")) != std::string::npos) {
            std::string raw_xml_data_temp_cpy = raw_xml_data_second_cpy;

            raw_xml_data_second_cpy.erase(0, newline_pos + 1);
            raw_xml_data_temp_cpy.erase(newline_pos, raw_xml_data_temp_cpy.length());
            last_newline_pos = newline_pos;

            lines.push_back(raw_xml_data_temp_cpy);
        }

        std::vector<std::string>::iterator it = remove_if(lines.begin(), lines.end(), std::mem_fn(&std::string::empty));
        lines.erase(it, lines.end());

        std::cout << raw_xml_data_cpy << std::endl;

        for (int i = 0; i <= lines.size() - 1; i++) {
            std::string line_cpy = lines.at(i);
            std::string line_second_cpy = lines.at(i);

            line_second_cpy.erase(0, 1);
            line_second_cpy.erase(line_second_cpy.find_first_of(">"), line_second_cpy.length());
            std::string key_name = line_second_cpy;

            line_cpy.erase(0, line_cpy.find_first_of(">") + 1);
            line_cpy.erase(line_cpy.find_last_of("</") - 1, line_cpy.length());

            std::string key_data;
            if (line_cpy.length() <= 0)
                key_data = ' ';
            else
                key_data = line_cpy;

            this->parsed_xml_data[key_name] = key_data;
        }
        return is_parsed = true;
    }
    auto get_data_member(std::string keyname) {
        if (this->is_parsed)
            return this->parsed_xml_data[keyname];
        else
            return this->raw_xml_data;
    }

private:
    void create_delimeters() {
        /* declare start and end tags here, this data will be deleted */
        /* keep the <inGameInfo> tags here, didn't write any code to handle it ("sub section") */
        std::vector<std::string> deletion_tags_start = { "<inGameInfo>" };
        std::vector<std::string> deletion_tags_end = { "</inGameInfo>" };

        if (deletion_tags_start.size() >= 1 && deletion_tags_end.size() >= 1 && deletion_tags_start.size() == deletion_tags_end.size()) {
            for (int i = 0; i <= deletion_tags_start.size() - 1; i++) {
                this->delimeters.push_back(std::make_pair(deletion_tags_start.at(i), deletion_tags_end.at(i)));
            }
        }
    }
    static size_t curl_writecallbackfn(void* contents, size_t size, size_t nmemb, void* userp) {
        ((std::string*)userp)->append((char*)contents, size * nmemb);
        return size * nmemb;
    }
private:
    /* read buffer, hold the raw xml data recieved from curl*/
    std::string raw_xml_data;

    /* holds tags pairs (delimeters) */
    std::vector<std::pair<std::string, std::string>> delimeters;

    /* parsed xml data buffer */
    bool is_parsed = false;
    std::map<std::string, std::string> parsed_xml_data;
};