
Diesel IR Documentation
=======================

The Diesel IR is a representation of Diesel's source code, capturing its syntax and semantics in a structured format. It consists of nodes that represent various language constructs such as variables, constants, functions, and control flow.

Nodes
-----

### Program

The `Program` node represents the entire Diesel program.

    
    Program {
      functions: [Function]
      variables: [Variable]
    }
        

### Function

The `Function` node represents a function in Diesel.

    
    Function {
      name: str
      parameters: [Parameter]
      return_type: Type
      body: [Statement]
      modifiers: [FunctionModifier]
    }
        

### Parameter

The `Parameter` node represents a function parameter.

    
    Parameter {
      name: str
      type: Type
    }
        

### Variable

The `Variable` node represents a variable declaration.

    
    Variable {
      name: str
      type: Type
      value: Expression
      constant: bool
    }
        

### Type

The `Type` node represents a type in Diesel.

    
    Type {
      name: str
      bit_size: int
      signed: bool
    }
        

### Statement

The `Statement` node represents a statement in Diesel. It can be one of several types.

    
    Statement {
      type: StatementType
      data: any
    }
        

#### StatementType

`StatementType` can be:

*   `Assignment`
*   `FunctionCall`
*   `If`
*   `While`
*   `For`
*   `Return`

### Assignment

The `Assignment` node represents a variable assignment.

    
    Assignment {
      variable: str
      value: Expression
    }
        

### FunctionCall

The `FunctionCall` node represents a function call.

    
    FunctionCall {
      name: str
      arguments: [Expression]
    }
        

### If

The `If` node represents an if-else statement.

    
    If {
      condition: Expression
      then_branch: [Statement]
      else_branch: [Statement]
    }
        

### While

The `While` node represents a while loop.

    
    While {
      condition: Expression
      body: [Statement]
    }
        

### For

The `For` node represents a for loop.

    
    For {
      iterator: str
      collection: Expression
      body: [Statement]
    }
        

### Return

The `Return` node represents a return statement.

    
    Return {
      value: Expression
    }
        

### Expression

The `Expression` node represents an expression in Diesel. It can be one of several types.

    
    Expression {
      type: ExpressionType
      data: any
    }
        

#### ExpressionType

`ExpressionType` can be:

*   `Literal`
*   `Variable`
*   `BinaryOperation`
*   `UnaryOperation`
*   `FunctionCall`

### Literal

The `Literal` node represents a literal value.

    
    Literal {
      value: any
      type: Type
    }
        

### VariableReference

The `VariableReference` node represents a reference to a variable.

    
    VariableReference {
      name: str
    }
        

### BinaryOperation

The `BinaryOperation` node represents a binary operation.

    
    BinaryOperation {
      operator: str
      left: Expression
      right: Expression
    }
        

### UnaryOperation

The `UnaryOperation` node represents a unary operation.

    
    UnaryOperation {
      operator: str
      operand: Expression
    }
        

Function Modifiers
------------------

Function modifiers alter the behavior of functions. In Diesel, the `Entry` modifier designates the entry point of the program.

    
    FunctionModifier {
      type: ModifierType
    }
        

#### ModifierType

`ModifierType` can be:

*   `Entry`

Example IR Representation
-------------------------

Here is an example of Diesel code and its corresponding IR.

### Diesel Code

    
    const Pi: float64 = 3.14159;
    
    func Main(): void {
      var Radius: float64 = 5.0;
      var Area: float64 = Pi * Radius * Radius;
      Output("Area: ");
      Output(Area);
    }
    
    func Output(Value: str): void {
      #[ Print the value ]#
    }
        

### Corresponding IR

    
    Program {
      functions: [
        Function {
          name: "Main"
          parameters: []
          return_type: Type { name: "void" }
          body: [
            Variable {
              name: "Radius"
              type: Type { name: "float64" }
              value: Literal { value: 5.0, type: Type { name: "float64" } }
              constant: false
            }
            Variable {
              name: "Area"
              type: Type { name: "float64" }
              value: BinaryOperation {
                operator: "*"
                left: BinaryOperation {
                  operator: "*"
                  left: VariableReference { name: "Pi" }
                  right: VariableReference { name: "Radius" }
                }
                right: VariableReference { name: "Radius" }
              }
              constant: false
            }
            FunctionCall {
              name: "Output"
              arguments: [Literal { value: "Area: ", type: Type { name: "str" } }]
            }
            FunctionCall {
              name: "Output"
              arguments: [VariableReference { name: "Area" }]
            }
          ]
          modifiers: [FunctionModifier { type: "Entry" }]
        }
        Function {
          name: "Output"
          parameters: [
            Parameter { name: "Value", type: Type { name: "str" } }
          ]
          return_type: Type { name: "void" }
          body: []
          modifiers: []
        }
      ]
      variables: [
        Variable {
          name: "Pi"
          type: Type { name: "float64" }
          value: Literal { value: 3.14159, type: Type { name: "float64" } }
          constant: true
        }
      ]
    }