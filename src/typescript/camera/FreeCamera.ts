import { IFreeCamera } from '../interfaces/camera';
import { PerspectiveCamera } from './PerspectiveCamera';

export class FreeCamera extends PerspectiveCamera implements IFreeCamera
{
    constructor(protected _cameraInstance: WasmExportedFreeCamera)
    {
        super(_cameraInstance);
    }

    public playback(): void
    {
        this._cameraInstance.Playback();
    }
}