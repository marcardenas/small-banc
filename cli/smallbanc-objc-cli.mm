#include <Foundation/Foundation.h>

#include "smallbanc-objc-impl.h"

int main(
    int argc,
    char* argv[]
)
{
    ArgsObjc* args = [[ArgsObjc alloc] init];
    ParserObjc* parser = [[ParserObjc alloc] initWithArgs:args];

    [parser set_args:argc argv:argv];
    [parser parse];

    if( args.help )
    {
        printf("Help requested\n");
    }
    else
    {
        printf("No help requested\n");
    }

    [args dealloc];

    return 0;
}