Hi there, I just wanna say, that my algorithm can't handle the 5th test (contained in input file of your conditions in zip file which we got)on x86 build environment in command line, so you should use x64 build environment to handle it.

I suggest to use x64 Native Tools Command Prompt for VS 2019, you should have it, if you have VS 2019.

and the reason of this situation is that, you want us to use dynamic array instead of static array, so where is the problem?

hold on I will tell you what I could understand, and please if I'm wrong just mention the right answer for that to me in the file of the marks, so when we build a dynamic array we use 8 bytes for the pointer of that array, and in our situation we represent a bucket in cuckoo filter by dynamic array contained 4  elements size each 1 bytes and 8 bytes for the pointer too. so the sum of these is 12 bytes for each bucket, and in your 5th test we have 10000 videos and 10001 users, and we should build for each user a filter and the size of this filter is (10000*1.06)*12 and the size of all filters is (10000*1.06)*12*10001*8(the last 8 becuase we have also dynamic array to save the buckets and for each user we need 8 bytes for pointer on his filter)and this should be a crazy number of GBs, which we need in our memory to handle it.


That's all what I wanted to say.

Thank's for your attention on this file!



 