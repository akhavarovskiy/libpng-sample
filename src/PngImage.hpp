#ifndef PNG_IMAGE_HPP__
#define PNG_IMAGE_HPP__

#include <vector>
#include <cstdint>
#include <string>
#include <filesystem>
#include <png.h>

namespace image
{
  enum PNG_BIT_DEPTH : uint8_t {
    ONE     = (1 << 0),
    TWO     = (1 << 1),
    FOUR    = (1 << 2),
    EIGHT   = (1 << 3),
    SIXTEEN = (1 << 4),
  };

  enum PNG_COLOR_TYPE : uint8_t {
    MASK_PALETTE  = 1,
    MASK_COLOR    = 2,
    MASK_ALPHA    = 4,
  };

  enum PNG_COLOR : uint8_t {
    GRAY       = 0,
    PALETTE    = (PNG_COLOR_TYPE::MASK_COLOR | PNG_COLOR_TYPE::MASK_PALETTE),
    RGB        = (PNG_COLOR_TYPE::MASK_COLOR),
    ALPHA      = (PNG_COLOR_TYPE::MASK_COLOR | PNG_COLOR_TYPE::MASK_ALPHA),
    GRAY_ALPHA = (PNG_COLOR_TYPE::MASK_ALPHA),
    UNKNOWN    = 0xFF,
  };

  template<typename T>
  union PNG_PIXEL_RGB {
    T data[3];
    struct {
      T r;
      T g;
      T b;
    } rgb;
  };
  typedef PNG_PIXEL_RGB<uint8_t>           PNG_PIXEL_RGB_8;
  typedef std::vector<PNG_PIXEL_RGB_8>     PNG_PIXEL_RGB_8_ROW;
  typedef std::vector<PNG_PIXEL_RGB_8_ROW> PNG_PIXEL_RGB_8_ROWS;

  typedef PNG_PIXEL_RGB<uint16_t>           PNG_PIXEL_RGB_16;
  typedef std::vector<PNG_PIXEL_RGB_16>     PNG_PIXEL_RGB_16_ROW;
  typedef std::vector<PNG_PIXEL_RGB_16_ROW> PNG_PIXEL_RGB_16_ROWS;

  template<typename T>
  union PNG_PIXEL_RGBA {
    T data[4];
    struct {
      T r;
      T g;
      T b;
      T a;
    } rgba;
  };
  typedef PNG_PIXEL_RGBA<uint8_t>           PNG_PIXEL_RGBA_8;
  typedef std::vector<PNG_PIXEL_RGBA_8>     PNG_PIXEL_RGBA_8_ROW;
  typedef std::vector<PNG_PIXEL_RGBA_8_ROW> PNG_PIXEL_RGBA_8_ROWS;

  typedef PNG_PIXEL_RGBA<uint16_t>           PNG_PIXEL_RGBA_16;
  typedef std::vector<PNG_PIXEL_RGBA_16>     PNG_PIXEL_RGBA_16_ROW;
  typedef std::vector<PNG_PIXEL_RGBA_16_ROW> PNG_PIXEL_RGBA_16_ROWS;

  class PNG {
  public:
    /// @brief Construct PNG structure from file path
    /// @param other
    PNG(std::filesystem::path path);

    /// @brief Construct PNG structure from memory
    /// @param other
    PNG(std::vector<uint8_t> & data);

    /// @brief Copy Constructor
    /// @param other
    PNG(const PNG& other);

    /// @brief Move Constructor
    /// @param other
    PNG(PNG&& other);

    /// @brief Destructor
    ~PNG(void);

    uint64_t      size     (void) const;
    uint32_t      width    (void) const;
    uint32_t      height   (void) const;
    uint8_t       channels (void) const;
    PNG_COLOR     colorType(void) const;
    PNG_BIT_DEPTH bitDepth (void) const;

    // Converted the image to RGBA16 and return it
    PNG_PIXEL_RGBA_16_ROWS asRGBA16(void) const;

    // Update the image from RGBA16
    void          fromRGBA16(PNG_PIXEL_RGBA_16_ROWS& rows);

    // Save the file
    void          saveToFile(std::filesystem::path path);
  protected:
    void          loadImageFromFile(FILE* fp);
  private:
    void*         m_png;
    void*         m_info;
    uint32_t      m_width;
    uint32_t      m_height;
    uint8_t       m_channels;
    PNG_COLOR     m_color_type;
    PNG_BIT_DEPTH m_bit_depth;
    uint16_t**    m_rows;
  };
} // namespace image
#endif // PNG_IMAGE_HPP__