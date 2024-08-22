#include <iostream>
#include <vulkan/vulkan.h>

 struct MyTextureData {
    VkDescriptorSet DS; 
    int Width;
    int Height;
    int Channels;

    VkImageView ImageView;
    VkImage Image;
    VkDeviceMemory ImageMemory;
    VkSampler Sampler;
    VkBuffer UploadBuffer;
    VkDeviceMemory UploadBufferMemory;

    MyTextureData() { memset(this, 0, sizeof(*this)); }
};

namespace MyApp {

    void RenderUI( MyTextureData my_texture);

}
