import NodejsLua from ".";

const lua = new NodejsLua();

//enable default lua libs (vars, functions like print)
lua.openLibs();
lua.doString("print('Hello, from Lua!')");

//set number 5 as global variable test
lua.pushNumber(5);
lua.setGlobal("test");
lua.doString("print('Test value is: ' .. test .. '. Invoked from lua!')");

//get global var value as number
lua.getGlobal("test");
const value = lua.toNumber(-1);
console.log(`Test value is: ${value}. Invoked from js!`);

//get global var type
lua.getGlobal("test");
const type = lua.getType(-1);
console.log(`Is Bool: ${type == NodejsLua.TYPES.BOOL}`);

//closes lua state
lua.close();
