console.log("Hello World");
console.log("Hola Mundo");
console.log('Hola Mundo');
let s = "nuevo";
console.log("Hola " + s + " Mundo");
console.log(2+3*4);
console.log(Infinity - Infinity);
console.log(typeof s);
console.log(typeof null);
console.log(typeof NaN);
console.log(1==2);
let num = 2
console.log(num == 2);
num = "2";
console.log(num == 2);
console.log(num === 2);
console.log(typeof num);
console.log(null * 8);
console.log("cinco" * 8);


// EJERCICIO DE SACAR PROMEDIO DE NUMEROS ALEATORIOS EN UN PROMPT
let prom1 = 0;
let prom2 = 0;
let n = prompt("Introduzca el numero de repeticiones: ") || 10; 
for(let i = 0; i < n; i++){
    let a = Math.random()*100;
    console.log(a);
    if(a >= 50){
        prom1 = prom1 + 1;
    }   
    else{
        prom2 = prom2 + 1;
    }
}

console.log("Mayor porcentaje");
console.log((prom1/n)*100);
console.log("Menor porcentaje");
console.log((prom2/n)*100);

const elementos = [
    "agua",
    "fuego",
    "viento",
    "aire"
];

console.log(typeof elementos);
console.log(elementos);
console.log(elementos.push("hierba"));
console.log(elementos.pop());
console.log(elementos.shift());
console.log(elementos);

console.log(elementos.unshift("hierba"));

for(let i = 0; i < elementos.length; i++){
    console.log(elementos[i]);
}

//  let i = 0;

elementos.forEach(function(elemento, index, array){
    console.log(elemento);
    console.log(index);
    console.log(array);
    // console.log(i);
});

elementos.forEach(elemento => {
    console.log(elemento);
})

console.log("APARTADOO");

const despliegaElemento = function(elemento){
    console.log(elemento);
}

//elementos.forEach(despliegaElemento);

const arregloFiltrado = elementos.filter((elemento) => elemento.startsWith('a'));
console.log(arregloFiltrado);

const arregloMayuscula = elementos.map((elemento) => elemento.charAt(0).toUpperCase() + elemento.slice(1));
console.log(arregloMayuscula);

const cantidadNoInicianConA = elementos.reduce((acc, elemento) => {
if (!elemento.startsWith('a')) {
    acc++;
}
return acc;
}, 0);

console.log(cantidadNoInicianConA);

const estudiante = {
    nombre: "Juan",
    apellidos: "Perez",
    edad: 20,
    promedio: 8.5,
    semestre : 6,
    status : "aprobado",
    tutor: {
        nombre: "Carlos",
        correo: "Lara@gmail.com"
    }
};

console.log(estudiante);

console.log(estudiante.tutor);

console.log(estudiante.tutor.correo);

for(let [llave,valor] of Object.entries(estudiante)){
    console.log(llave + ": " + valor);
}

const proceso1 = {
    operacion : "a = 1 + 2",
    mensaje : "1 + 2",
    resultado : 3
}

const proceso2 = {
    operacion : "b = 3 + 4",
    mensaje : "3 + 4",

    resultado : 7
}
const proceso3 = {
    operacion : "c = 5 + 6",
    mensaje : "5 + 6",
    resultado : 11,
}

const procesos = [proceso1,proceso2,proceso3];
let quantum = 2;
const round_robin = function(procesos,quantum){

    for(let i = 0; i < procesos.length; i++){
        console.log("Proceso: ");
        console.log(procesos[i].operacion);
    }
    for(let i = 0; i < procesos.length; i++){
        console.log("Proceso: " + i+1);

        console.log(procesos[i].mensaje);
    }

    for(let i = 0; i < procesos.length; i++){
        console.log("Proceso: " + i+1);

        console.log(procesos[i].resultado);
    }
}


console.log("Round Robin");
console.log(round_robin(procesos, 2));
console.log("Quantum: " + quantum);

// Crer un objeto

const proceso = new Object();
proceso.nombre = "Proceso 1";
proceso.duracion = 10;

proceso.fn = function(a,b){
    return a + b;
}

console.log(proceso.fn(2,3));
console.log(proceso.nombre);

let resultado = eval(proceso.fn(2,3));

console.log(resultado);
console.log(proceso);

// SERIALIZACION Y DESERIALIZACION
let serializacion = JSON.stringify(proceso);

console.log(serializacion);

let deserializacion = JSON.parse(serializacion);

console.log(deserializacion);

// FUNCIONES DE ORDEN SUPERIOR
let sumar = function(a,b){
    return a + b
}


let repetir =  function(n,action){
    for(let i = 0; i < n; i++){
        action(i);
    }
}
repetir(3,console.log);
