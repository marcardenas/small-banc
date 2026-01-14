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

    if( [args.helpCommand length] != 0 )
    {
        [parser print_help:args.helpCommand];
    }

    if( [args.command length] == 0 )
    {
        [parser print_help:@""];
    }

    [args dealloc];

    return 0;
}