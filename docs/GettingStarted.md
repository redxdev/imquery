# Getting Started with imquery

Welcome to imquery! This tutorial will get you started with writing simple image
transformations by using imquery's scripting language, imq. This tutorial assumes you have at least
some familiarity with existing scripting languages such as Python or Lua.

This tutorial assumes you have already built imquery and iqc. It is suggested you build in
release mode, as debug mode slows down imquery quite a bit.

You may either run examples by running `iqc` and then entering commands interactively,
or you may save commands in a file and run them with `iqc -f filename.imq`.

## Comments

Comments start with `#` and continue until the end of the line.

## Types

imq is inspired by languages like Lua and Python, and as such is dynamically typed. The full
list of possible types are as follows:

* Nil
* Bool
* Integer
* Float
* Object/QObject
* Function/QFunction

Strings are not currently supported, but may be in the future.

All types except for _Object_ and _Function_ are value types - when passing them around, you
copy them. _Object_/_Function_ are reference types - unless you explicitly copy it, you will
always pass a reference to it rather than the value itself.

_Function_ is a bit weird in this regard, but we'll come back to it later.

### Nil

Nil represents having _no value_. The only valid value for Nil is `nil`.

### Bool

The Bool type can hold either `true` or `false`.

### Integer

The Integer type contains a single 32-bit signed integer.

### Float

The Float type contains a single 32-bit float. Float constants always have a decimal. For example,
`42` is an integer, while `42.` is a float.

### Object

The Object type contains a reference to something. That something could be many things - an array,
a table, a color, an image, etc...

Objects are always passed by reference.

### Function

The Function type contains an executable function.

Functions are always passed by reference.

## Variables

Defining a variable is simple:

    foo = 123;

Here, we defined `foo` as the integer `123`. We can also redefine the variable freely:

    foo = false;

In the rare case we want to delete a variable from the current context, we can use delete:

    delete foo;

## Expressions

Expressions are anything that can return a value. If you are using `iqc` in interactive mode,
you can see the result of an expression by entering it and then a semicolon like so:

    > 1 + 4;
    5

Expressions include function calls as well:

    > sin(pi / 2.);
    1

You can set variables with expressions as you might expect...

    > foo = sin(pi / 2.);

and then retrieve them:

    > foo;
    1

Trying to access a variable that hasn't been set results in an error:

    > bar;
    runtime error: line 1:0: Unknown variable "bar"

## Colors

The _Color_ (or _QColor_) type is an important _Object_ in imq. Colors are a set of 4 floats:
red, green, blue, and alpha. Colors can be created through the following syntax:

    {red, green, blue, alpha}

For example:

    > {1., 2., 3., 4.};
    {1,2,3,4}

Color expressions only accept floats.

    > {1, 2, 3, 4};
    runtime error: line 1:0: Expected floats for color components

If you don't specify an alpha value, it defaults to `1.`:

    > {1., 2., 3.};
    {1,2,3,1}

If you only specify a single value, it applies to all components except alpha:

    > {3.};
    {3,3,3,1}

If you specify two components, it applies the first to red/green/blue and the second to
alpha:

    > {3., 5.};
    {3,3,3,5}

All of these shorthands are designed to make writing colors easier. Note that there is no
"default" color expression, and as such this will result in a syntax error:

    > {};
    parse error: line 1:1: no viable alternative at input '{}'

Colors can also be used in mathematical expressions. Generally, an expression between an
integer or float and a color will result in that expression being applied to each component
individually:

    > {1.,2.,3.,4.} + 5;
    {6,7,8,9}
    
This is equivalent to `{1. + 5, 2. + 5, 3. + 5, 4. + 5}`

An expression between two colors results in the expression being run on each pair of components:

    > {1.,2.,3.,4} - {1.,2.,3.,4}
    {0,0,0,0}

This is equivalent to `{1. - 1., 2. - 2., 3. - 3., 4. - 4.}`.

You can also retrieve a component from a color by name (red/green/blue/alpha) or index:

    > foo = {1.,2.,3.,4.};
    > foo.red;
    1
    > foo[0];
    1
    > foo.green;
    2
    > foo[1];
    2

There are also shorthands for components:

    > foo.r;
    1
    > foo.g;
    2
    > foo.b;
    3
    > foo.a;
    4
    
Normally, you'd also be able to set fields and indices the same way you set variables, but
the Color object is, in fact, immutable and it will throw an error if you try.

    > foo.r = 25.;
    runtime error: line 1:0: Object QColor is immutable.

Now, color components usually fall within the range of 0.0 to 1.0, but for the sake of math
(and because HDR allows you to break these bounds) you are allowed to go outside that range.
Saving an image (see below) will result in some weird colors if you keep it that way, but you
can also clamp colors like this:

    > foo = {3.,-10.}
    > foo
    {3,3,3,-10.}
    > foo = foo.clamp();
    > foo
    {1,1,1,0}

Note that `clamp` returns a new color and does not modify the original (remember, colors are
immutable).

## Images

Images are a central part of imq, since that's the point of the language in the first place.
Images are _Objects_, and can be created by calling the `image` function.

With no arguments, `image` creates an empty image of size 0x0:

    > image();
    QImage[0,0]

With two arguments, `image` creates an image of the specified width and height with all pixels
set to black `{0., 0., 0., 1.}`:

    > image(20, 30)
    QImage[20,30]

Finally, you may add a third argument of type _Color_ to specify the initial pixel colors:

    > image(20, 30, {1., 0., 0.})
    QImage[20,30]
    
The above will create a 20x30 solid red image.

You can get the size of an image with width/height (or w/h):

    > foo = image(20, 30);
    > foo.width
    20
    > foo.w
    20
    > foo.height
    30
    > foo.h
    30

You can retrieve pixels with the `pixel` function (coordinates start at 0,0 and end at
width - 1, height - 1)...

    > foo = image(20, 30);
    > foo.pixel(2, 3)
    {0,0,0,1}

Or you can set pixels:

    > foo.pixel(2, 3, {1., 0., 0.});
    > foo.pixel(2, 3);
    {1,0,0,1}

You can also clamp all pixels:

    > foo = image(20, 30, {10.});
    > foo.pixel(2, 3);
    {10,10,10,1)
    > foo.clamp();
    > foo.pixel(2, 3);
    {1,1,1,1}
    
If you haven't noticed, we've been doing operations on images that directly affect the image
object. Images _are_ mutable, unlike colors, as we don't want to be copying large images around
in memory.

## Inputs and Outputs

In order to load and save images, you must define inputs and outputs in your scripts. These look
like normal variable definitions, except they have a bit attached to the beginning:

    > in myInput = image();
    > out myOutput = image(myInput.w, myInput.h);

Inputs and outputs may not be redefined once they have been defined. They also must be set to
some value, even if that value is nil.

If a script you are running has inputs or outputs, you may specify them to iqc like so:

    iqc -i "myInput=images/myImage.png" -o "myOutput=images/myOutput.png"

All inputs and outputs must be filepaths to images at this time, and outputs are always saved
in PNG format.

If an input is specified on the command line, then it is checked against your input definition
to make sure they are of the same type. That is why you will often see an input being defined
as an empty image - all that matters is that the input has the type _image_.

Outputs are checked when the script ends.

## Selections

Now that you know about images and colors, it's time for selections. Selections are how you
process pixels from one image through an expression into another image. For example:

    > in input = image();
    > out output = image(input.w, input.h);
    > output: color from input;

The last line here is a selection - it applies an expression to each pixel of `input` and then
copies the result into `output`. In this case, we're just copying the input image to `output`.

Within the select expression, there are some new variables defined. These variables include:

* x, y - the coordinates of the current pixel
* color - the color of the current pixel

Here's a selection that inverts an image instead:

    > output: 1 - {color.r, color.g, color.b, -color.a} from image;

The `-color.a` is because we don't want to invert the alpha, so we invert it a second time to
get the original result.

What if we want to only select parts of an image? Well, there's the `where` clause.

    > output: 1 - {color.r, color.g, color.b, -color.a} from image where x < 30;

Now only pixels that have an x-coordinate of less than 30 will be written to the output image.
Any pixels that don't match the `where` clause won't be touched in `output`.

We can also do other things with the where clause:

    > output: color from image where color.r < 0.5;

The where clause has access to the same variables that the main expression does.

Finally, we have the `else` clause. If a pixel fails to match the `where` clause, then the
`else` clause will be used in place of the main expression:

    > output: color from image where color.r < 0.5 else {1., 0., 0.};
    
Here, we write any pixels with a red value of < 0.5 normally, but otherwise we use a pixel color
of pure red.

## If Statements

imq also supports your standard assortment of if statements and loops. If statements have
the following syntax:

    if foo {
        # do something
    }
    else if bar {
        # do something else
    }
    else {
        # do something else
    }
    
The `else if` clause can be repeated, and both the `else if` and `else` clauses are optional.
Here are some relevant operators:

* `or`, `and`: logical or/and operators. In other languages, these are usually `||` and `&&`
* `not`: logical not operator. In other languages, this is usually `!`.
* `<=`, `==`, `>=`, `!=`, `<`, `>`: equality and comparison operators

## Loops

imq supports three types of loops: `for`, `while`, and `loop`.

The for loop is in the following format:

    for foo = 0; foo < 10; foo = foo + 1; {
        # do something
    }
    
Note that there is a final semicolon before the curly brace. The general format of the for loop
is this:

    for init_statement; check_expression; increment_statement; {
        statements
    }

You may omit both the init and increment statements, but their semicolons must stay:

    for ; true; ; {
        # do something infinitely
    }
    
Is an infinite loop.

The while loop is similar:

    while foo {
        # do something
    }
    
while loops just take a single expression.

If you need to write an infinite loop, use `loop` rather than while, as there are some
optimizations that imq can make if you do so:

    loop {
        # do something infinitely
    }

### Breaking out of loops

You can break out of loops much the same way you do in other languages:

    loop {
        if (some_condition) {
            break; # exits the loop
        }
    }

This works on all three types of loops.

`continue` statements are not currently supported.

## Defining Functions

There are two ways to define functions in imq. The first is to define a named function:

    func foo(a, b, c) {
        print(a);
        return b + c;
    }
    
This function when called will print the first argument to the terminal, and then return
the second and third arguments added together.

The other way to define a function is anonymously. This looks similar to lambda syntax in
other languages like C#:

    foo = (a, b, c) => {
        print(a);
        return b + c;
    }; # note the semicolon! this is still setting a variable, which requires a semicolon.

Anonymous functions have the advantage of being expressions - you can define the function right
inside a calculation. That said, you can still use a named function inside an expression - it
just has to have been defined somewhere prior.

Anonymous functions also have a shorthand if all they need to do is return the result of a
single expression:

    foo = (a, b) => a + b;

Calling `foo` will return the result adding the first and second arguments. Since you may
use anonymous function definitions as expressions, the following is valid:

    > ((a, b) => a + b)(4, 6);
    10

All functions defined inside imq are known as script-defined functions, as opposed to native
functions.

### Closures

All script-defined functions act as closures on their context (environment). They store a
reference to their parent context, and always use that when executing.

For example, knowing that an `if` statement has its own scope and given this script:

    myFunc = nil;
    if true {
        foo = 5;
        myFunc = () => foo;
    }
    
    foo = 20;

Would a call to `myFunc` return `5` or `20`?

The answer is `5`, as the function is defined in the scope of the `if` statement. Since it
`closes` around the `if` statement's context, it will see that `foo` is defined there before
it sees that `foo` is defined in the outer context.

Now, if we change the script like so:

    myFunc = nil;
    foo = nil;
    if true {
        foo = 5;
        myFunc = () => foo;
    }
    
    foo = 20;

`myFunc` will now return 20. This is because we defined `foo` before the `if` statement - and
there fore we aren't defining a new variable called `foo` inside the `if` statement but instead
we are setting an existing one. Therefore, the function `myFunc` will find that `foo` doesn't
exist in the `if` statement's context, and instead check the context above that which contains
our global `foo` definition.