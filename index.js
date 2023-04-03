const NodejsLua = require("bindings")("NodejsLua").NodejsLua;

NodejsLua.TYPES = {
    "NIL": 0,
    "NUMBER": 1,
    "BOOL": 2,
    "STRING": 3,
    "TABLE": 4,
    "FUNCTION": 5,
    "USER_DATA": 6,
    "THREAD": 7,
    "LIGHTUSERDATA": 8
}

module.exports = NodejsLua;
