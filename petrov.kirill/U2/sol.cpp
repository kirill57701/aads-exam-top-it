#include "sol.hpp"
#include <iostream>
#include <fstream>

namespace petrov
{
  template<class T>
  void grow_vec(T* data, size_t& c, size_t& s)
  {
    size_t new_c = c * 2;
    T* new_d = new T[new_c];
    for (size_t i = 0; i < s; ++i)
    {
      new_d[i] = data[i];
    }
    delete[] data;
    data = new_d;
    c = new_c;
  }

  size_t cycle(int argc, char** argv)
  {
    if (argc < 2 || argc > 3)
    {
      std::cerr << "too much\n";
      return 1;
    }
    std::string inf = "", df = "";
    for (int i = 1; i < argc; ++i) {
      std::string arg = argv[i];
      if (!arg.rfind("in:", 0)) {
        if (!inf.empty()) {
          std::cerr << "dubl\n";
          return 1;
        }
        inf = arg.substr(3);
      } else if (!arg.rfind("data:", 0)) {
        if (!df.empty()) {
          std::cerr << "dubl\n";
          return 1;
        }
        df = arg.substr(5);
      } else {
        std::cerr << "inval\n";
        return 1;
      }
    }
    if (df.empty())
    {
      std::cerr << "err\n";
      return 1;
    }
    Pvec ps = {nullptr, 0, 0};
    Mvec ms = {nullptr, 0, 0};

    if (!inf.empty())
    {
      std::ifstream fin(inf.c_str());
      if (!fin)
      {
        std::cerr << "err\n";
        delete[] ps.dat;
        delete[] ms.dat;
        return 2;
      }
      std::string l = "";
      while (std::getline(fin, l))
      {
        size_t id = 0;
        while (id < l.size() && (l[id] == ' ' || l[id] == '\t')) {
          id = id + 1;
        }
        if (id == l.size()) {
          continue;
        }
        if (l[id] < '0' || l[id] > '9') {
          continue;
        }
        size_t num = 0;
        while (id < l.size() && l[id] >= '0' && l[id] <= '9') {
          num = num * 10 + static_cast<size_t>(l[id] - '0');
          id = id + 1;
        }
        while (id < l.size() && (l[id] == ' ' || l[id] == '\t')) {
          id = id + 1;
        }
        if (id == l.size()) {
          continue;
        }
        std::string txt = l.substr(id);
        bool dup = false;
        for (size_t i = 0; i < ps.s; ++i) {
          if (ps.dat[i].id == num) {
            dup = true;
            break;
          }
        }
        if (dup) {
          continue;
        }
        if (ps.s == ps.c) {
          size_t nc = ps.c * 2;
          if (nc == 0) {
            nc = 2;
          }
          Person* nd = new Person[nc];
          for (size_t i = 0; i < ps.s; ++i) {
            nd[i] = ps.dat[i];
          }
          delete[] ps.dat;
          ps.dat = nd;
          ps.c = nc;
        }
        ps.dat[ps.s].id = num;
        ps.dat[ps.s].info = txt;
        ps.dat[ps.s].h_i = 1;
        ps.dat[ps.s].del = 0;
        ps.s = ps.s + 1;
      }
    }

    std::ifstream f_dt(df.c_str());
    if (!f_dt) {
      std::cerr << "open err\n";
      delete[] ps.dat;
      delete[] ms.dat;
      return 2;
    }
    size_t id1 = 0;
    size_t id2 = 0;
    size_t len = 0;
    while (f_dt >> id1 >> id2 >> len) {
      if (id1 == id2) {
        continue;
      }
      bool f1 = false;
      bool f2 = false;
      for (size_t i = 0; i < ps.s; ++i) {
        if (ps.dat[i].id == id1) {
          f1 = true;
        }
        if (ps.dat[i].id == id2) {
          f2 = true;
        }
      }
      if (!f1) {
        if (ps.s == ps.c) {
          size_t nc = ps.c * 2;
          if (nc == 0) {
            nc = 2;
          }
          Person* nd = new Person[nc];
          for (size_t i = 0; i < ps.s; ++i) {
            nd[i] = ps.dat[i];
          }
          delete[] ps.dat;
          ps.dat = nd;
          ps.c = nc;
        }
        ps.dat[ps.s].id = id1;
        ps.dat[ps.s].info = "";
        ps.dat[ps.s].h_i = 0;
        ps.dat[ps.s].del = 0;
        ps.s = ps.s + 1;
      }
      if (!f2) {
        if (ps.s == ps.c) {
          size_t nc = ps.c * 2;
          if (nc == 0) {
            nc = 2;
          }
          Person* nd = new Person[nc];
          for (size_t i = 0; i < ps.s; ++i) {
            nd[i] = ps.dat[i];
          }
          delete[] ps.dat;
          ps.dat = nd;
          ps.c = nc;
        }
        ps.dat[ps.s].id = id2;
        ps.dat[ps.s].info = "";
        ps.dat[ps.s].h_i = 0;
        ps.dat[ps.s].del = 0;
        ps.s = ps.s + 1;
      }
      if (ms.s == ms.c) {
        size_t nc = ms.c * 2;
        if (nc == 0) {
          nc = 2;
        }
        Meeting* nd = new Meeting[nc];
        for (size_t i = 0; i < ms.s; ++i) {
          nd[i] = ms.dat[i];
        }
        delete[] ms.dat;
        ms.dat = nd;
        ms.c = nc;
      }
      ms.dat[ms.s].i1 = id1;
      ms.dat[ms.s].i2 = id2;
      ms.dat[ms.s].t = len;
      ms.dat[ms.s].del = 0;
      ms.s = ms.s + 1;
    }
    if (f_dt.fail() && !f_dt.eof()) {
      std::cerr << "read err\n";
      delete[] ps.dat;
      delete[] ms.dat;
      return 3;
    }
  }
}
