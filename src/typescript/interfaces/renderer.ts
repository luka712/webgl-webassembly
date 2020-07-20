export interface IRenderer
{
    geometryColor(r: number, g: number, b: number, a: number): void;
    clearColor(r: number, g: number, b: number, a: number): void;
}