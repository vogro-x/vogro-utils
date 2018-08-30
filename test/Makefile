all:
	make parse_header
	make parse_request_line
	make url_match
	make trim_string 
	
parse_header:
	g++ -std=c++11 parse_header_test.cpp -o parse_header
	./parse_header
	rm parse_header

parse_request_line:
	g++ -std=c++11 parse_request_line_test.cpp -o parse_request_line
	./parse_request_line
	rm parse_request_line

url_match:
	g++ -std=c++11 url_match_test.cpp -o url_match
	./url_match
	rm url_match

trim_string:
	g++ -std=c++11 trim_string_test.cpp -o trim_string
	./trim_string
	rm trim_string
