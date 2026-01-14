#import <Foundation/Foundation.h>
#import <smallbanc/actions.hpp>

namespace smallbanc::argparse
{
    struct Args;
    class Parser;
}

@interface ArgsObjc : NSObject
- (NSString*) helpCommand;
- (NSString*) command;
- (instancetype)init;
- (void *)instance;
@end

@interface ParserObjc : NSObject
- (void)set_args:(int)argc argv:(char**)argv;
- (void)parse;
- (void)print_help:(NSString*)command;
- (instancetype)initWithArgs:(ArgsObjc*)args;
@end

@interface IActionsObjc : NSObject

@end

@interface AddClientActionObjc : IActionsObjc

@end