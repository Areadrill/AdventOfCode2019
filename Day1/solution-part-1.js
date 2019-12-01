const fs = require('fs');

const input = fs.readFileSync('input.txt', 'utf-8');
const inputTok = input.split('\n').map(tok => parseInt(tok.trim()));
const sol = inputTok.map(tok => Math.floor(tok/3) - 2).reduce((accum, cur) => accum+cur, 0);

console.log(sol);


