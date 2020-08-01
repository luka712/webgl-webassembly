import { IPerspectiveCamera } from '../interfaces/camera';
import { Camera } from './Camera';
import { ISceneManager } from '../interfaces/scene';


export class PerspectiveCamera  extends Camera implements IPerspectiveCamera
{
    constructor(protected _cameraInstance: WasmExportedPerspectiveCamera)
    {
        super(_cameraInstance);
    }
}