/* Copyright (c) 2007 Google Inc.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/


// The GDataGatherInput stream is an input stream implementation that is to be
// instantiated with an NSArray of NSData objects.  It works in the traditional
// scatter/gather vector I/O model.  Rather than allocating a big NSData object
// to hold all of the data and performing a copy into that object, the
// GDataGatherInputStream will maintain a reference to the NSArray and read from
// each NSData in turn as the read method is called.  You should not alter the
// underlying set of NSData objects until all read operations on this input
// stream have completed.

#import <Foundation/Foundation.h>

#if (MAC_OS_X_VERSION_MAX_ALLOWED <= MAC_OS_X_VERSION_10_4) || defined(GDATA_TARGET_NAMESPACE)
  // we need NSInteger for the 10.4 SDK, or we're using target namespace macros
  #import "GDataDefines.h"
#endif

#undef GDATA_NSSTREAM_DELEGATE
#if TARGET_OS_MAC && !TARGET_OS_IPHONE && (MAC_OS_X_VERSION_MAX_ALLOWED >= 1060)
 #define GDATA_NSSTREAM_DELEGATE <NSStreamDelegate>
#else
 #define GDATA_NSSTREAM_DELEGATE <NSStreamDelegate>
#endif

@interface GDataGatherInputStream : NSInputStream GDATA_NSSTREAM_DELEGATE {

  NSArray* dataArray_;   // NSDatas that should be "gathered" and streamed.
  NSUInteger arrayIndex_;       // Index in the array of the current NSData.
  long long dataOffset_; // Offset in the current NSData we are processing.

  id delegate_;          // WEAK, not retained: stream delegate, defaults to self

  // Since various undocumented methods get called on a stream, we'll
  // use a 1-byte dummy stream object to handle all unexpected messages.
  // Actual reads from the stream we will perform using the data array, not
  // from the dummy stream.
  NSInputStream* dummyStream_;
  NSData* dummyData_;
}

+ (NSInputStream *)streamWithArray:(NSArray *)dataArray;

- (id)initWithArray:(NSArray *)dataArray;

@end
