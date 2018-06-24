//
//  Constants.h
//  FlappyGame
//
//  Created by rMBP on 2014/03/28.
//
//

#ifndef FlappyGame_Constants_h
#define FlappyGame_Constants_h

#define kZindexBackground 0
#define kZindexCloudSlow 5
#define kZindexCloudFast 8
#define kZindexPipe 30

#define kZindexFlappy 100

#define kFlappyStateStopped 0
#define kFlappyStateMoving 1
#define kFlappyStartSpeedY 400
#define kFlappyStartX 240

#define kCloudScaleSlow 0.4
#define kCloudScaleFast 0.85

#define kCloudRestartX 100
#define kCloudDestinationX -50

#define kCloudSpeedSlow 5.0
#define kCloudSpeedFast 1.0

#define kPipeStateInactive 0
#define kPipeStateActive 1

#define kPipeOffsetX 100
#define kPipeInactiveX -1000

#define kPipeSpawnMinTime 0.5
#define kPipeSpawnMaxVariance 5

#define kSingleGapTop 480
#define kSingleGapBottom 160
#define kSingleGapMax 320
#define kSingleGapMin 160

#define kDoubleGapTop 540
#define kDoubleGapBottom 160
#define kDoubleGapMax 280
#define kDoubleGapMin 120

#define GRAVITY -1000.00

#endif
