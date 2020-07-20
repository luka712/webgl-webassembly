import { WasmRenderer } from "./renderer/WasmRenderer";
import { IFileManager } from "./interfaces/file";
import { WasmFileManager } from "./io/WasmFileManager";
import { IRenderer } from "./interfaces/renderer";

export class NJS
{
    private _renderer: IRenderer;
    private _fileManager: IFileManager;

    constructor(module: IModule)
    {   
        this._renderer = new WasmRenderer(module);
        this._fileManager = new WasmFileManager(module);
    }

    public get renderer(): IRenderer 
    {
        return this._renderer;
    }

    public get fileManager(): IFileManager
    {
        return this._fileManager;
    }
}

// @ts-ignore
window.NJS = NJS;