

import requests

command = "<osm-script output=\"json\" timeout=\"90000\">\
  <union>\
    <query type=\"way\">\
      <has-kv k=\"highway\" regv=\"motorway|motorway_link|trunk|trunk_link|primary|primary_link|secondary|secondary_link|tertiary|tertiary_link|unclassified|unclassified_link|residential|residential_link|service|service_link|living_street\"/>\
     <bbox-query e=\"4.277487\" w=\"-2.014497\" n=\"49.473253\" s=\"46.464866\"/>\
    </query>\
  </union>\
  <!-- print results -->\
  <print mode=\"body\"/>\
  <recurse type=\"down\"/>\
  <print mode=\"skeleton\" order=\"quadtile\"/>\
</osm-script>"

# all france : <bbox-query e=\"8.297352\" w=\"-4.908836\" n=\"51.443333\" s=\"42.092404\"/>\
# all france smaller : <bbox-query e=\"6.021624\" w=\"-2.014497\" n=\"49.473253\" s=\"42.092404\"/>\
# all france even smaller : <bbox-query e=\"4.277487\" w=\"-2.014497\" n=\"49.473253\" s=\"46.464866\"/>\
# Roche-sur-Yon - Angouleme : <bbox-query e=\"0.653200\" w=\"-1.476296\" n=\"46.701405\" s=\"44.597395\"/>\

filename = "all_france.json"
url = "http://overpass-api.de/api/interpreter"

r = requests.post(url, data = "data=" + command, stream=True)
with open(filename, 'wb') as f:
    for chunk in r.iter_content(chunk_size=1024): 
      if chunk:
        f.write(chunk)