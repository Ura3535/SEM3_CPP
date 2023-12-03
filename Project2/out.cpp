#include "header.h"
#include <iomanip>	//setpresision

Output::Output(std::string file)
	: out(file, std::ios::out)
{
	out << std::fixed << std::setprecision(6);
	out
		<< "<!DOCTYPE html>\n"
		<< "<html lang=\"en\">\n"
		<< "<head>\n"
		<< " <meta charset=\"UTF-8\" />\n"
		<< " <title>Program Project2 Tests</title>\n"
		<< "</head>\n\n"
		<< "<body>\n"
		<< " <font size='3'>\n";
}

Output::~Output()
{
	out
		<< " </font>\n"
		<< "</body>\n"
		<< "</html>\n";
	out.close();
}

void Output::outputTestInTable(const Test& test)
{
	out
		<< " <table border='1'>\n"
		<< " <tr><th colspan='2'>" << test.title << "</th></tr>\n"
		<< " <tr>\n"
		<< "  <th>Type (or K)</th>\n"
		<< "  <th>Duration (sec)</th>\n"
		<< " </tr>\n";
	for(auto const& x : test.results)
		out
			<< " <tr>\n"
			<< " <td>" << x.first << "</td>\n"
			<< " <td>" << x.second << "</td>\n"
			<< " </tr>\n";
	out
		<< " </table>\n"
		<< " <br>\n";

	return;
}