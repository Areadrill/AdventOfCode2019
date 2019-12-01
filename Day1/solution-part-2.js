const fs = require('fs');

const massToRequirement = (mass) => Math.floor(mass/3) - 2;

const input = fs.readFileSync('input.txt', 'utf-8');
const inputTok = input.split('\n').map(tok => parseInt(tok.trim()));

let requirement = inputTok.map(massToRequirement);
let requirements =  requirement;

while (requirement.filter(el => el > 0).length !== 0) {
    requirement = requirement.map(massToRequirement);
    requirements = [...requirements, ...requirement];
}

const sol = requirements.reduce((accum, cur) => cur > 0 ? accum+cur : accum, 0);

console.log(sol);
