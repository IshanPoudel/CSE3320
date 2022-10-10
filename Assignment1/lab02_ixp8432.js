// Ishan Poudel
// UTA ID: 1001838432
// October 5 , 2022

//Create array called inputtable
const inputtable = [1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 , 10]

//Use map function to create the three tables.
const fiveTable = inputtable.map(x => x*5)
console.log(fiveTable)

const thirteenTable = inputtable.map(x=>x*13)
console.log(thirteenTable)

const squaresTable = inputtable.map(x => Math.pow(x , 2))
console.log(squaresTable)

//Create  an array with first 100 numbers and filter based on criteria(odd and divisible by 5)
const oddMultiplesofFive = Array.from(Array(100).keys()).filter(x => x % 2 ==1 ).filter(x => x % 5==0)
console.log(oddMultiplesofFive)

// Create an array with first 100 numbers and reduce based on even and multiple of 7
const initialValue = 0;
const sumofEvenMultiplesofSeven = Array.from(Array(100).keys()).filter(x => x%2 ==0).filter(x=> x%7==0).reduce( (previousValue, currentValue) => previousValue + currentValue,
  initialValue);
console.log(sumofEvenMultiplesofSeven)


function cylinder_volume(r){
    return function (h) {
        return 3.14*r*r*h;
    }
}

//Create a currying function
console.log(cylinder_volume(5)(10))

console.log(cylinder_volume(5)(17))

console.log(cylinder_volume(5)(11))

//Create a table
makeTag = function(beginTag, endTag){ 
   return function(textcontent){ 
      return beginTag +textcontent +endTag; 
   } 
} 

//write varibales
var write_text = makeTag( "<th>" , "</th>" );
var write_the_tags = makeTag("<tr>" , "</tr>");

//print the table

console.log(write_the_tags(write_text("Ishan") + write_text("Poudel")+write_text(20)))
console.log(write_the_tags(write_text("John") + write_text("Doe")+write_text(20)))












