require 'apache2'

function handle(r)
  r.content_type = 'text/plain'
  r.headers_out['Clock'] = r:clock()
  r:puts('lua\n')
  return apache2.OK
end
