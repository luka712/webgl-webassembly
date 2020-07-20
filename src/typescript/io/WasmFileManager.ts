import { IFileManager } from "../interfaces/file";

export class WasmFileManager implements IFileManager
{
    private _wasmReadFile: ((file: string) => string);

    constructor(module: IModule)
    {
        this._wasmReadFile = module.cwrap("read_file", "string", ["string"]);
    }
    
    public readFile(file: string): string
    {
        return this._wasmReadFile(file);
    }
}