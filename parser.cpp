#include <fstream>
#include <iostream>
#include <exception>
#include <iterator>

#include "parser.h"

parser::parser(const std::string& value) {
    read_file(value);
    cur_position = json_buffer.begin();
}

parser::~parser() {}

void parser::read_file(const std::string& file_name) {
    std::ifstream in(file_name);
    std::string tmp;
    if (in.is_open()) {
        while (!in.eof()) {
            in >> tmp;
            json_buffer += tmp + ' ';
        }
    }
    else {
        std::cout << "File name is incorrect! We will parsing empty JSON.";
        return;
    }
    in.close();
}

void parser::parse() {   
    while (cur_position < json_buffer.end()) {
        try {
            separate_next_element(result);
        }
        catch(std::exception e) {
            std::cerr << e.what() << std::endl;
            return;
        }

    }
}

void parser::separate_next_element(std::string& buffer) {
    if (check_separator(*cur_position)) {
        char tmp = *cur_position;
        int cur_separator_type = separator_type(tmp);
        ++cur_position;
        // cur_separator_type == 1 is ' " '
        if (cur_separator_type == 1) {
            do_action_with_quote(buffer);
        }
        // cur_separator_type == 2 is ' , '
        else if (cur_separator_type == 2) {
            do_action_with_comma(buffer);
        }
        //  cur_separator_type == 3 is '{'
        else if (cur_separator_type == 3) {
            do_action_with_open_figure_brackets(buffer);
        }       
        // cur_separator_type == 4 is ' [ '
        else if (cur_separator_type == 4) {
            do_action_with_open_array_brackets(buffer);
        }
        // cur_separator_type == 5 is '{'
        else if (cur_separator_type == 5) {
            do_action_with_close_bracket(buffer);
        }
        // cur_separator_type == 6 is ' ] '
        else if (cur_separator_type == 6) {
            do_action_with_close_array_brackets(buffer);
        }
        // cur_separator_type == 7 is '  '
        else if (cur_separator_type == 7) {
            do_action_with_spaces(buffer);
        }
        // cur_separator_type == 8 is ':'
        else if (cur_separator_type == 8) {
            do_action_with_colon(buffer);
        }
    }
    else {
        ++cur_position;
    }
}

void parser::do_action_with_quote(std::string& buffer) {
    extract_word(buffer);
}

void parser::do_action_with_comma(std::string& buffer) {
    buffer += '\n';
    insert_tabs(buffer);
}

void parser::do_action_with_open_figure_brackets(std::string& buffer) {
    open_bracket++;
    if (open_bracket > 1) {
        buffer += '\n';
        insert_tabs(buffer);
    }
    if (separator_type(*cur_position) == 7) { ++cur_position; }
    if (!check_separator(*cur_position) || separator_type(*cur_position) != 1) {
        throw std::runtime_error("Expected \"");
    }
    else {
        ++cur_position;
        extract_word(buffer);
    }
}

void parser::do_action_with_open_array_brackets(std::string& buffer) {
    array_flag = true;
    open_array_bracket++;
    buffer += "Array of \n";
    if (separator_type(*cur_position) == 7) {
        ++cur_position;
    }
    insert_tabs(buffer);
    separate_next_element(buffer);
}
void parser::do_action_with_close_bracket(std::string& buffer) {
    open_bracket--;
    ++cur_position;
    if (open_bracket < 0 || (open_bracket == 0 && cur_position < json_buffer.end() - 1)) {
        throw std::runtime_error("Open brackets not equal close brackets");
    }
    buffer += '\n';
}

void parser::do_action_with_close_array_brackets(std::string& buffer) {
    open_array_bracket--;
    if (open_array_bracket == 0) {
        array_flag = false;
    }
}

void parser::do_action_with_spaces(std::string& buffer) {
    // This method does nothing but I decided that spaces should be processed. And if we will
    // decide to improve the parser, then most likely this method will be necessary. 
    // I understand that it is stupid to leave methods with empty body, but here it seems 
    // a good solution
    return;
}

void parser::do_action_with_colon(std::string& buffer) {
    buffer += ": ";
    ++cur_position;
}

void parser::extract_word(std::string& buffer) {
    size_t pos_current_quote = json_buffer.size() - (json_buffer.end() - cur_position);
    size_t pos_next_quote = json_buffer.find('\"', pos_current_quote);
    buffer += json_buffer.substr(pos_current_quote, pos_next_quote - pos_current_quote);
    if (cur_position + (pos_next_quote - pos_current_quote) < json_buffer.end()) {
        cur_position += (pos_next_quote - pos_current_quote) + 1;
    }
}

bool parser::check_separator(char ch) {
    if (ch == '\"' || ch == ',' || ch == '{' || ch == '[' || ch == '}' || ch == ']'
        || ch == ' ' || ch == ':') {
        return true;
    }
    else {
        return false;
    }
}
int parser::separator_type(char ch) {
    if (ch == '\"') { return 1; }
    else if (ch == ',') { return 2; }
    else if (ch == '{') { return 3; }
    else if (ch == '[') { return 4; }
    else if (ch == '}') { return 5; }
    else if (ch == ']') { return 6; }
    else if (ch == ' ') { return 7; }
    else if (ch == ':') { return 8; }
}

void parser::insert_tabs(std::string& buffer) {
    if (array_flag) {
        for (size_t i = 0; i < open_array_bracket; i++) {
            buffer += '\t';
        }
    }
    else {
        for (size_t i = 1; i < open_bracket; i++) {
            buffer += '\t';
        }
    }
}

void parser::print() {
    /*for (auto it = parsing_result.begin(); it != parsing_result.end(); ++it) {
        std::cout << it->first;
        print_list(it->second);
        std::cout << std::endl;
    } */ 
    std::cout << result;
}