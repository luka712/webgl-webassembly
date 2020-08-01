import { ISceneManager, IScene } from '../interfaces/scene';


export class SceneManager implements ISceneManager
{
    private readonly _instance: WasmExporetedSceneManager;
    private readonly _scene: IScene;

    constructor(private _module: IModule)
    {
        this._instance = _module.SceneManager.GetInstance();
    }

    public get current(): IScene
    {
        const wasmScene = this._instance.GetCurrent();
        
    }
}