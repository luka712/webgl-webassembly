import { ICamera } from "./camera";

export interface ISceneManager 
{
    readonly current: IScene;
}

export interface IScene 
{
    getCamera<T extends ICamera>(): T;
}
