// -*- mode: C++; c-file-style: "stroustrup"; c-basic-offset: 4; indent-tabs-mode: nil; -*-
////////////////////////////////////////////////////////////////////
//
// This file is a part of the UPPAAL toolkit.
// Copyright (c) 1995 - 2006, Uppsala University and Aalborg University.
// All right reserved.
//
///////////////////////////////////////////////////////////////////

#include "io/License.h"

#include <string>
#include <iostream>

using io::License;
using namespace std;

std::string untag(const char* msg)
{
    std::string res(msg);
    for (size_t i = 0; i < res.length(); ++i) {
        if (res[i] == '$') {
            res.erase(i, 1);
            for (; i < res.length(); ++i) {
                switch (res[i]) {
                case ' ':
                case '\t':
                case '\r':
                case '\n':
                case ':': goto stop_word;
                case '_': res[i] = ' ';
                default:;
                }
            }
        stop_word:;
        }
    }
    if (res.length() > 0) {
        char last = res[res.length() - 1];
        if (last != '.' && last != '!' && last != '?') {
            res += '.';
        }
    }
    return res;
}

int main(int argc, char* argv[])
{
    License lic(argv[0], argc < 2 ? NULL : argv[1], "license.txt");

    cout << "Status: " << untag(License::status2str(lic.checkStatus())) << "\n";

    for (License::const_iterator i = lic.begin(); i != lic.end(); ++i) {
        cout << i->first << "=" << i->second << "\n";
    }

#ifdef SUPER_VERBOSE
    cout << "features:";
    for (License::feature_iterator i = lic.beginFeature(); i != lic.endFeature(); ++i) {
        cout << ' ' << i->first;
    }
    cout << '\n'
         << "has(editor)=" << lic.hasFeature("editor") << '\n'
         << "has(simulator)=" << lic.hasFeature("simulator") << '\n'
         << "has(verifier)=" << lic.hasFeature("verifier") << '\n'
         << "has(tiga)=" << lic.hasFeature("tiga") << '\n'
         << "has(cora)=" << lic.hasFeature("cora") << '\n'
         << "has(tron)=" << lic.hasFeature("tron") << '\n'
         << "has(pro)=" << lic.hasFeature("pro") << '\n';
#endif

#ifdef __MINGW32__
    cout << "Please press Enter...\n";
    getchar();
#endif

    return 0;
}
