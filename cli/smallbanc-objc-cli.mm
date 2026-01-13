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

    if( [[args helpCommand] length] > 0 )
    {
        printf("Help requested for: %s\n", [[args helpCommand] UTF8String]);
    }
    else
    {
        printf("No help requested\n");
    }

    [args dealloc];

    return 0;
}