import { ICamera } from '../interfaces/camera';
import { ISceneManager } from '../interfaces/scene';
export class Camera implements ICamera
{
    constructor(protected _cameraInstance: WasmExportedCamera)
    {
        
    }
}