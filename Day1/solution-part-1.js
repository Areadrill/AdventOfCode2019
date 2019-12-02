const fs = require('fs');

const input = fs.readFileSync('input.txt', 'utf-8');
const inputTok = input.split('\n');
const sol = inputTok.reduce((accum, cur) => accum + (Math.floor(parseInt(cur.trim())/3) - 2), 0);

console.log(sol);


