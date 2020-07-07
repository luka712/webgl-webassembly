import { WasmRenderer } from "./renderer/WasmRenderer";
import { IRenderer } from "./renderer/IRenderer";

export class NJS
{
    private _renderer: IRenderer;

    constructor(module: IModule)
    {   
        this._renderer = new WasmRenderer(module);
    }

    public get renderer(): IRenderer 
    {
        return this._renderer;
    }
}

// @ts-ignore
window.NJS = NJS;