#include <iostream>
#include <fstream>
#include <string>
#include "person.hpp"

int main(int argc, char** argv)
{
  if (argc > 3)
  {
    return 1;
  }

  std::string file_in = "";
  std::string file_out = "";

  for (int i = 1; i < argc; ++i)
  {
    std::string arg = argv[i];
    if (!arg.find("in:"))
    {
      file_in = arg.substr(3);
    }
    else if (!arg.find("out:"))
    {
      file_out = arg.substr(4);
    }
    else
    {
      return 1;
    }
  }

  std::istream* in = &std::cin;
  std::ostream* out = &std::cout;
  std::ifstream fin;
  std::ofstream fout;

  if (file_in != "")
  {
    fin.open(file_in);
    if (!fin.is_open())
    {
      return 2;
    }
    in = &fin;
  }

  if (file_out != "")
  {
    fout.open(file_out);
    if (!fout.is_open())
    {
      return 2;
    }
    out = &fout;
  }

  petrov::Person* vec = nullptr;
  size_t s = 0, c = 0, ok = 0, err = 0;
  while(*in)
  {
    size_t id_v;
    if (!(*in >> id_v))
    {
      in->clear();
      std::string trash;
      if (std::getline(*in, trash))
      {
        size_t q = 0;
        for (size_t i = 0; i < trash.size(); ++i)
        {
          if (trash[i] != ' ' && trash[i] != '\n' && trash[i] == '\r')
          {
            q = 1;
            break;
          }
        }
      }
      err += q;
    }
    continue;
  }
  return 0;
}
