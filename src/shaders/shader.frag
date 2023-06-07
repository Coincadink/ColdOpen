#version 450

layout(location = 0) out vec4 outColor;

struct Ray
{
    vec3 origin;
    vec3 direction;
};

float hitSphere(vec3 center, float radius, Ray ray)
{
    vec3 oc = ray.origin - center;
    float a = dot(ray.direction, ray.direction);
    float b = 2.0 * dot(oc, ray.direction);
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
    {
        return -1.0;
    }
    else
    {
        return (-b - sqrt(discriminant)) / (2.0 * a);
    }
}

vec3 unitVector(vec3 vec)
{
    return vec / length(vec);
}

vec3 at(Ray ray, float t)
{
    return ray.origin + ray.direction * t;
}

vec3 rayColor(Ray ray) 
{
    float t = hitSphere(vec3(0.0, 0.0, -1.0), 0.5, ray);
    if (t > 0.0)
    {
        vec3 N = unitVector(at(ray, t) - vec3(0.0, 0.0, -1.0));
        return 0.5 * vec3(N.x + 1, N.y + 1, N.z + 1);
    }

    vec3 unitDirection = unitVector(ray.direction);
    t = 0.5 * (unitDirection.y + 1.0);
    return (1.0 - t) * vec3(0.7294, 0.3373, 0.7882) + t * vec3(1.0, 0.4471, 0.4471);
}

void main() 
{   
    vec2 iResolution = vec2(900, 900);
    float aspectResolution = iResolution.x / iResolution.y;

    // Camera

    float viewportHeight = 2.0;
    float viewportWidth = viewportHeight * aspectResolution;
    float focalLength = 1.0;

    vec3 origin = vec3(0.0, 0.0, 0.0);
    vec3 horizontal = vec3(viewportWidth, 0.0, 0.0);
    vec3 vertical = vec3(0.0, viewportHeight, 0.0);
    vec3 lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - vec3(0.0, 0.0, focalLength);

    // Ray Trace

    vec2 uv = vec2(gl_FragCoord.x / iResolution.x, (iResolution.y - gl_FragCoord.y) / iResolution);

    Ray ray = Ray(origin, lowerLeftCorner + uv.x * horizontal + uv.y * vertical - origin);
    vec3 pixelColor = rayColor(ray);

    outColor = vec4(pixelColor, 1.0);
}