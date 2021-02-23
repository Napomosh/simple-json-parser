/**
*	@file
*	This is head file of Test task "JSON simple parser".
**/

#ifndef _PARSER_H_
#define _PARSER_H_

#include <string>

/**
*	@date 23.02.2021
*
*	Simple parser of JSON files.
*	
**/ 

class parser {
public:
    /**
    *	Default constructor. Constructs our parser. It receives json file name.
    *	@param value - File name with json data
    **/
    parser(const std::string& value);

    /**
    *	Copy constructor. I dont know how we can use this constructor so I decided to remove it
    *	@param p - parser object to coping
    **/
    parser(const parser& p) = delete;

    /**
    *	Copy assignment operator. I dont know how we can use this operator so I decided to remove it
    *	@param rhs - another object to use as data source
    **/
    parser& operator=(const parser& rhs) = delete;

    /**
    *	Destructor. Parser hadn't dynamic objects and destructor destroy nothing.
    *	@param none
    **/
    ~parser();

    /**
    *	This method read json from file to string buffer
    *	@param file_name - name of file for reading
    **/
    void read_file(const std::string& file_name);

    /**
    *	This method controls all parsing process. It controls iterators to avoid out of
    *   bounds of json_buffer. And catches all exceptions from separate_next_element().
    *	@param none
    **/
    void parse();

    /**
    *   It prints result to the console. Use std::cout.
    *	@param none
    **/
    void print();

private:
    /**
    *   JSON data is stored here
    **/
    std::string json_buffer;

    /**
    *   Iterator on current position in json buffer
    **/
    std::string::iterator cur_position;

    /**
    *   String with result of parsing
    **/
    std::string result;

    /**
    *   Variable storing count of open figure bracket (using in insert_tabs())
    **/
    int open_bracket = 0;

    /**
    *   Variable storing count of open array bracket (using in insert_tabs())
    **/
    int open_array_bracket = 0;

    /**
    *   Array_flag - flag which defines is it array or not
    **/
    bool array_flag = false;

    /**
    *	This private method separate next elements. Also it controls iterator 
    *   (increment it when it is necessary). 
    *   Only two options are possible: a separator and a word. But any words starts with 
    *   quotes (separators). This function determines which separator is marked with 
    *   iterator (cur_position) using method separator_type().
    *   This method will determine what to do depending on the type of separator. These 
    *   actions are described in other private methods do_action_xxx()
    *   
    *	@param buffer - in this string we will save the extracting word or separator
    **/
    void separate_next_element(std::string& buffer);

    /**
    *   It returns separator type
    *   1 - quotes (")
    *   2 - comma (,)
    *   3 - open figure bracket ({)
    *   4 - open array bracket ([)
    *   5 - close figure bracket (})
    *   6 - close array bracket (])
    *   7 - space ( )
    *   8 - colon (:)
    *	@param ch - separator wich we will analysis
    *   @return code of sepsrator
    **/
    int separator_type(char ch);

    /**
    *   Removes quotes and extract word (or phrase) wich bounded with 2 quotes.
    *   For example, "this phrase will be extract", "but this phrase will be not extract"
    *	@param buffer - in this string we will save the extracting word or phrase
    **/
    void extract_word(std::string& buffer);

    /**
    *   Insert tabulations (\t) for formatting output
    *	@param buffer - in this string we will save the extracting word or phrase
    **/
    void insert_tabs(std::string& buffer);

    /**
    *   Check char symbol: separator or not?
    *	@param ch - symbol for checking
    **/
    bool check_separator(char ch);

    /**
    *   Determines what we should do when we extract open figure brackets
    *	@param buffer - in this string we will save the extracting word or phrase
    **/
    void do_action_with_open_figure_brackets(std::string& buffer);

    /**
    *   Determines what we should do when we extract colon
    *	@param buffer - in this string we will save the extracting word or phrase
    **/
    void do_action_with_colon(std::string& buffer);

    /**
    *   Determines what we should do when we extract close figure brackets
    *	@param buffer - in this string we will save the extracting word or phrase
    **/
    void do_action_with_close_bracket(std::string& buffer);

    /**
    *   Determines what we should do when we extract quote
    *	@param buffer - in this string we will save the extracting word or phrase
    **/
    void do_action_with_quote(std::string& buffer);

    /**
    *   Determines what we should do when we extract comma
    *	@param buffer - in this string we will save the extracting word or phrase
    **/
    void do_action_with_comma(std::string& buffer);

    /**
    *   Determines what we should do when we extract open array brackets
    *	@param buffer - in this string we will save the extracting word or phrase
    **/
    void do_action_with_open_array_brackets(std::string& buffer);

    /**
    *   Determines what we should do when we extract close array brackets
    *	@param buffer - in this string we will save the extracting word or phrase
    **/
    void do_action_with_close_array_brackets(std::string& buffer);

    /**
    *   Determines what we should do when we extract spaces
    *	@param buffer - in this string we will save the extracting word or phrase
    **/
    void do_action_with_spaces(std::string& buffer);
};

#endif // _PARSER_H_
