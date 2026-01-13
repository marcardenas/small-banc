#include <smallbanc/argparse.hpp>
#include "smallbanc-objc-impl.h"

@interface ArgsObjc ()
{
    smallbanc::argparse::Args* _cppInstance;
}
@end

@interface ParserObjc ()
{
    smallbanc::argparse::Parser* _cppInstance;
}
@end

@implementation ArgsObjc

- (instancetype)init
{
    self = [super init];

    if( self )
    {
        _cppInstance = new smallbanc::argparse::Args();
    }
    
    return self;
}

- (void)dealloc
{
    delete static_cast<smallbanc::argparse::Args*>( _cppInstance );
    [super dealloc];
}
- (void *) instance 
{
    return _cppInstance;
}

- (NSString*) helpCommand 
{
    const std::string& str = static_cast<smallbanc::argparse::Args*>( _cppInstance )->help_command;
    return [NSString stringWithUTF8String: str.c_str()];
}
@end

@implementation ParserObjc
- (instancetype)initWithArgs:(ArgsObjc*)args
{
    self = [super init];

    if( self )
    {
        if( args.instance ) 
        {
            smallbanc::argparse::Args* cppArgs = static_cast<smallbanc::argparse::Args*>( args.instance );
            _cppInstance = new smallbanc::argparse::Parser( *cppArgs );
        }
    }

    return self;
}
- (void)dealloc
{
    delete static_cast<smallbanc::argparse::Parser*>( _cppInstance );
    [super dealloc];
}
- (void) set_args:(int)argc argv:(char **)argv 
{
    smallbanc::argparse::Parser* cppParser = static_cast<smallbanc::argparse::Parser*>( _cppInstance );
    cppParser->set_args( argc, argv );
}
- (void) parse 
{
    smallbanc::argparse::Parser* cppParser = static_cast<smallbanc::argparse::Parser*>( _cppInstance );
    cppParser->parse();
}
@end