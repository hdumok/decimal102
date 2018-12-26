
# Node NAPI 尝试
* 简单实现了将 数字，字符串数字 转换成 10位精度的2位小数的功能
* 超过精度范围的, 返回0
* 无法解析的，返回0

## Example
```
console.log(decimal(12345678.22111)) 
=> 12345678.22

console.log(decimal('11.22111'))
=> 11.22

console.log(decimal(-11.22111))
=> -11.22

console.log(decimal('-11.22111')) 
=> -11.22

console.log(decimal('a')) 
=> 0

console.log(decimal(123456789.22111)) 
=> 0
```