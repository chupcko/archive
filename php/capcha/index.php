<?

  function image_char(&$image, &$font, $x, $y, $char, $r, $g, $b)
  {
    $color = imagecolorallocatealpha($image, $r, $g, $b, 75);
    imagechar($image, $font, $x, $y, $char, $color);
  }
  
  function image_get_red(&$image, $x, $y)
  {
    return imagecolorat($image, $x, $y)>>16&0xff;
  }

  function image_get_green(&$image, $x, $y)
  {
    return imagecolorat($image, $x, $y)>>8&0xff;
  }

  function image_get_blue(&$image, $x, $y)
  {
    return imagecolorat($image, $x, $y)&0xff;
  }

  header("Content-type: image/png");
  $font = imageloadfont("font.gdf");
  $font_width = imagefontwidth($font);
  $font_height = imagefontheight($font);
  $image = imagecreatetruecolor(2*$font_width, $font_height);
  $white = imagecolorallocate($image, 255, 255, 255);
  imagefilledrectangle($image, 0, 0, 2*$font_width-1,  $font_height-1, $white);
  imagealphablending($image, true);
  image_char($image, $font, 2, 2, '2', 255, 0, 0);
  image_char($image, $font, 15, 7, '4', 0, 255, 0);
  image_char($image, $font, 32, 5, '6', 0, 0, 255);

  $im1 = imagecreatetruecolor(2*$font_width, $font_height);
  $white1 = imagecolorallocate($im1, 255, 0, 255);
  imagefilledrectangle($im1, 0, 0, 2*$font_width, $font_height, $white1);
  for($x = 1; $x < 2*$font_width-2; $x++)
    for($y = 1; $y < $font_height-2; $y++)
    {
      $r =image_get_red($image, $x, $y);
      $r +=image_get_red($image, $x-1, $y);
      $r +=image_get_red($image, $x, $y-1);
      $r +=image_get_red($image, $x, $y+1);
      $r +=image_get_red($image, $x+1, $y);
      $r /=5;
      $g =image_get_green($image, $x, $y);
      $g +=image_get_green($image, $x-1, $y);
      $g +=image_get_green($image, $x, $y-1);
      $g +=image_get_green($image, $x, $y+1);
      $g +=image_get_green($image, $x+1, $y);
      $g /=5;
      $b =image_get_blue($image, $x, $y);
      $b +=image_get_blue($image, $x-1, $y);
      $b +=image_get_blue($image, $x, $y-1);
      $b +=image_get_blue($image, $x, $y+1);
      $b +=image_get_blue($image, $x+1, $y);
      $b /=5;
      $color = imagecolorallocate($im1, $r, $g, $b);
      imagesetpixel($im1, $x, $y, $color);
    }
  imagepng($im1);
  imagedestroy($im1);
  imagedestroy($image);
  
?>
