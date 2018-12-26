var decimal = require('bindings')('main');

console.log(decimal(12345678.22111));
console.log(decimal('11.22111'));
console.log(decimal(-11.22111));
console.log(decimal('-11.22111'));
console.log(decimal('a'));
console.log(decimal(123456789.22111));
