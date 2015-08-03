# LightSTL
## LightSTL性能测试

### vector
(1)vector \<int\>
```cpp
//std::vector<double> vec   LightSTL::vector<double> vec 
clock_t t1 = clock();
for(int i = 0;i < test_size;i++){
    vec.push_back(i);
}
clock_t t2 = clock();
printf("%lfms\n",(double)1000*(t2-t1)/CLOCKS_PER_SEC);
```
测试结果：

![](https://github.com/gzwl/Image/blob/master/vectortest1.png)

(2)vector \<string\>
```cpp
//std::vector<std::string> vec  LightSTL::vector<std::string> vec
clock_t t1 = clock();
for(int i = 0;i < test_size;i++){
    vec.push_back(std::string("Hello World"));
}
clock_t t2 = clock();
printf("%lfms\n",(double)1000*(t2-t1)/CLOCKS_PER_SEC);
```
测试结果：

![](https://github.com/gzwl/Image/blob/master/vectortest2.png)
