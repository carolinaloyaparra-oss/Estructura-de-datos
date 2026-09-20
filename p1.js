let r = 3, c = 3;
let twoDArr = [
    [1, 2, 3],
    [4, 5, 6],
    [7, 8, 9]
];
let arr = new Array(9);


for (let x = 0; x < c; x++) {
    for (let y = 0; y < r; y++) {
        let k = x * r + y;
        arr[k] = twoDArr[y][x];
    }
}

console.log("Los elementos del array bidimensional son:");
for (let i = 0; i < r; i++) { // Se recorre por fila para mostrarla ordenada
    let fila = "";
    for (let j = 0; j < c; j++) {
        fila += twoDArr[i][j] + " ";
    }
    console.log(fila);
}


console.log("\nLos elementos del array unidimensional son:");
console.log(arr.join(" "));