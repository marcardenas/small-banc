#import <Foundation/Foundation.h>

namespace smallbanc::argparse
{
    struct Args;
    class Parser;
}

@interface ArgsObjc : NSObject

- (NSString*) helpCommand;

- (instancetype)init;
- (void *)instance;
@end

@interface ParserObjc : NSObject
- (void)set_args:(int)argc argv:(char**)argv;
- (void)parse;
- (instancetype)initWithArgs:(ArgsObjc*)args;
@end
