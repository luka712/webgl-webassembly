import { ISceneManager, IScene } from '../interfaces/scene';


export class SceneManager implements ISceneManager
{
    private readonly _instance: WasmExporetedSceneManager;

    constructor(private _module: IModule)
    {
        this._instance = _module.SceneManager.GetInstance();
    }

    public get current(): IScene
    {
        // translate 
        return this._instance.GetCurrent() as IScene;
    }
    scenes: import("../interfaces/scene").IScene[];
}