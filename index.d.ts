declare interface Types {
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

export default class NodejsLua {
    public static TYPES: Types;
    public openLibs(): void;
    public doString(code: string): void;
    public doFile(path: string): void;

    public pushString(str: string): void;
    public pushNumber(num: number): void;
    public pushBoolean(bool: boolean): void;
    public pushNil(): void;

    public setGlobal(str: string): void;
    public getGlobal(str: string): void;

    public getType(index: number): number;
    public toString(index: number): string;
    public toNumber(index: number): number;
    public toBoolean(index: number): boolean;

    public getTop(): number;
    public setTop(index: number): void;

    public replace(index: number): void;
    public pop(n: number): void;
    public setField(index: number, k: string): void;
    public getField(index: number, k: string): void;
    public yield(nresults: number): number;
    public collectGarbage(what: number, data: number): number;
    //public registerFunction(name: string, func: (...args: any[]) => void): void;

    public status(): number;
    public resume(nargs: number): void;
    public close(): void;
}
