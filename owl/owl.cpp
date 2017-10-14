//
//  owl.cpp
//  owl
//
//  Created by Sören König on 14.10.17.
//  Copyright © 2017 Sören König. All rights reserved.
//

#include <iostream>
#include "owl.hpp"
#include "owlPriv.hpp"

void owl::HelloWorld(const char * s)
{
    owlPriv *theObj = new owlPriv;
    theObj->HelloWorldPriv(s);
    delete theObj;
};

void owlPriv::HelloWorldPriv(const char * s) 
{
    std::cout << s << std::endl;
};

