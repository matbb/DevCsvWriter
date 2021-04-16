#pragma once

#include <cassert>
#include <exception>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

typedef struct {
    size_t precision = 5;
    size_t width = 15;
    std::string separator = "\t";
    std::string header_lead = "";
    bool fmt_is_scientific = true;
    std::string newline = "\n";
} DevCsvWriterSettings;

class DevCsvWriter {
public:
    DevCsvWriter(std::ostream& f,
                 DevCsvWriterSettings settings = DevCsvWriterSettings{})
        : settings(settings), f(f), i_line(0), i_column(0) {
        if (settings.fmt_is_scientific) f << std::scientific;
    }
    DevCsvWriter(std::string fname,
                 DevCsvWriterSettings settings = DevCsvWriterSettings{})
        : settings(settings), f(f_out), i_line(0), i_column(0) {
        f_out.open(fname.c_str(), std::ios_base::binary);
        if (settings.fmt_is_scientific) f << std::scientific;
    }
    ~DevCsvWriter() {
        if (i_line == 1) AddHeaderAndFirstRow();
        Flush();
    }

    bool IsOpen() const { return f_out.is_open(); }
    void Flush() { f.flush(); }
    void StartNewLine() {
        if (i_line == 1) {
            // Print header line, and add all values in first row
            AddHeaderAndFirstRow();
        }
        if (i_line > 0) f << settings.newline;
        values.clear();
        i_line++;
        i_column = 0;
    }
    void AddColumn(std::string column, double val) {
        if (i_line == 1) {
            columns.push_back(column);
            values.push_back(val);
        } else {
            assert(column == columns[i_column]);
            AddValue(val);
        }
        i_column++;
    }

private:
    void AddHeaderAndFirstRow() {
        f << settings.header_lead;
        for (size_t i = 0; i < columns.size(); ++i) {
            f << std::setw(settings.width) << columns[i] << settings.separator;
        }
        f << settings.newline;
        for (size_t i = 0; i < columns.size(); ++i) AddValue(values[i]);
    }
    void AddValue(double val) {
        f << std::setw(settings.width) << std::setprecision(settings.precision)
          << val << settings.separator;
    }

private:
    const DevCsvWriterSettings settings;
    std::ostream& f;
    std::ofstream f_out;
    std::vector<double> values;
    std::vector<std::string> columns;
    int i_line;
    int i_column;
};
