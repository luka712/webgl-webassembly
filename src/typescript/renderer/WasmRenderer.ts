import { IRenderer } from "./IRenderer";

export class WasmRenderer implements IRenderer 
{
    private _clearColor: (r: number, g: number, b: number, a: number) => void = null;
    private _geometryColor: (uniformName: string, r: number, g: number, b: number, a: number) => void = null;

    constructor(private module: IModule)
    {
        this._clearColor = module.cwrap("clear_color", "undefined", ["number", "number", "number", "number"]);
        // this._geometryColor = module.cwrap("geometry_color", "undefined", ["string", "number", "number", "number", "number"]);
        // var loadShader = module.cwrap("create_shader_material", "boolean", ["string", "string"]) as ((a: string, b: string) => number);
        // const res = loadShader(`
                
        //         attribute vec3 a_position;

        //         uniform mat4 u_projection;
        //         uniform mat4 u_view;
        //         uniform mat4 u_transform;

        //         void main() {
        //             gl_Position = u_projection * u_view * u_transform * vec4(a_position, 1.);
        //         }`,
        //     `
        //     precision mediump float;
        //     uniform vec4 u_color;

        //     void main()
        //     {
        //         gl_FragColor = u_color;
        //     }`);
    
        // const loadAttributeData = (module.cwrap("load_attribute_data", "undefined", ["number", "number", "number", "string"]) as (data: number, size: number, length: number, positionAttr: string) => void);
        // const loadIndicesData = (module.cwrap("load_indices_data", "undefined", ["number", "number"]) as (data: number, length: number) => void);
        
        // // triangle data
        // const _arrayF = new Float32Array([
        //     -0.5, -0.5, 0,
        //      0.5, -0.5, 0,
        //      0, 0.5, 0
        // ]);
        // const dataPtr = module._malloc(_arrayF.BYTES_PER_ELEMENT * _arrayF.length);
        // module.HEAPF32.set(_arrayF, dataPtr / _arrayF.BYTES_PER_ELEMENT);
        // loadAttributeData(dataPtr, 3, _arrayF.length, "a_position");
        // module._free(dataPtr);

        // // still not done 
        // // indices data 
        // const _indices = new Int32Array([
        //     0, 1, 2
        // ]);
        // const iDataPtr = module._malloc(_indices.BYTES_PER_ELEMENT * _indices.length);
        // module.HEAPU32.set(_indices, iDataPtr / _indices.BYTES_PER_ELEMENT);
        // loadIndicesData(iDataPtr, _indices.length);
        // module._free(iDataPtr);

        // this.geometryColor(0, 1, 0, 1);

    }

    public geometryColor(r: number, g: number, b: number, a: number): void
    {
        this._geometryColor("u_color", r, g, b, a);
    }

    public clearColor(r: number, g: number, b: number, a: number): void 
    {
        this._clearColor(r, g, b, a);
    }
}