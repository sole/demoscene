--[[----------------------------------------------------------------------------

escena.org invtro v2

by xplsv

music: eb7m
 code: sole

think you could make it better? do it!
here's the code :-P

----------------------------------------------------------------------------]]--
---- Constants ----

-- Color modes
COLOR_FLAT			   = 0
COLOR_SMOOTH		   = 1

-- Blending modes
BLENDING_ALPHABLEND    = 0
BLENDING_ADDITIVE      = 1
BLENDING_SUBSTRACTIVE  = 2
BLENDING_INVERT        = 3
BLENDING_INVERTDEST    = 4
BLENDING_MASK          = 5
BLENDING_MULTIPLY      = 6
BLENDING_INVMULTIPLY   = 7
BLENDING_COLORMULTIPLY = 8

-- Shapes
SHAPE_POINTS			= 0
SHAPE_LINES				= 1
SHAPE_LINE_STRIP		= 2
SHAPE_TRIANGLES			= 3
SHAPE_TRIANGLE_STRIP	= 4
SHAPE_QUADS				= 5
SHAPE_QUAD_STRIP		= 6
SHAPE_POLYGON			= 7

-- Fog
FOG_NONE				= 0
FOG_LINEAR				= 1
FOG_EXP					= 2
FOG_EXP2				= 3

---- Configuration ----

SCREEN_WIDTH	= 1024
SCREEN_HEIGHT	= 768

antialias(1)
--fullscreen(true)

size(SCREEN_WIDTH, SCREEN_HEIGHT)

-------------------------------------------------------------------------------

function my_progress_bar(val)
	background(0, 0, 0)
	ortho(1,1)
	stroke(0, 1, 0, 1)
	local i = 0
	while i < 1 do
		line(-0.5, i - 0.5, 0, -0.5 + val, i - 0.5, 0)
		i = i + 0.25
	end
	restoreProjection()
	swap_buffers()
end

function setup()
	windowTitle("escena.org dentro v2")
	
	math.randomseed(2)
	
	local setup_table = { Music, Gurrus, Ground, Rotobichos, Plancton, Texts }
	
	for key, value in pairs(setup_table) do
		my_progress_bar(key / #setup_table)
		value.setup()
	end
	
	global_t0 = 0

	
	setupIsDone()
	playMusicStream(Music.stream, 0)
end

-------------------------------------------------------------------------------

Vertex = {}
Vertex_mt = { __index = Vertex }

function Vertex:new(x, y, z)
	local v = {}
	v.x = x
	v.y = y
	v.z = z
	return setmetatable( v, Vertex_mt )
end

function Vertex:length()
	return math.sqrt(self.x * self.x + self.y * self.y + self.z * self.z)
end

function Vertex.cross(v1, v2) -- note the '.' and not ':' (Class method)
	local v = Vertex:new()
	
	v.x = v1.y * v2.z - v1.z * v2.y
	v.y = v1.z * v2.x - v1.x * v2.z
	v.z = v1.x * v2.y - v1.y * v2.x
	
	return v
end

function Vertex:unitary()
	local v = Vertex:new(self.x, self.y, self.z)
	local len = self:length()
	local invlen
	
	if(len == 0) then return Vertex:new() end
	
	invlen = 1.0 / len
	
	v.x = v.x * invlen
	v.y = v.y * invlen
	v.z = v.z * invlen
	
	return v
	
end

NumberUtils = {}
function NumberUtils.normalize(value, minimum, maximum)
	return (value - minimum) / (maximum - minimum)
end
       
function NumberUtils.interpolate(normValue, minimum, maximum)
	return minimum + (maximum - minimum) * normValue
end       

function NumberUtils.map(value, min1, max1, min2, max2)
	return NumberUtils.interpolate( NumberUtils.normalize(value, min1, max1), min2, max2)
end

Face = {}
Face_mt = { __index = Face }

function Face:new(a, b, c)
	local f = {}
	f.a = a
	f.b = b
	f.c = c
	f.normal = Vertex:new(0, 0, 0)
	return setmetatable( f, Face_mt )
end

function Face:updateNormal()
	local e1, e2, n
	
	e1 = Vertex:new(self.b.x - self.a.x, self.b.y - self.a.y, self.b.z - self.a.z)
	e2 = Vertex:new(self.c.x - self.b.x, self.c.y - self.b.y, self.c.z - self.b.z)
	n = Vertex.cross(e1, e2):unitary()
	
	self.normal.x = n.x
	self.normal.y = n.y
	self.normal.z = n.z	
	
	return n
end


Mesh = {}
Mesh_mt = { __index = Mesh }

function Mesh:new()
	local v
	v = Vertex:new(0, 0, 0)
	
	return setmetatable( { vertices = {}, faces = {}, current = v}, Mesh_mt )
end

function Mesh:face(a, b, c)
	local f = Face:new(a, b, c)
	f:updateNormal()
	table.insert(self.faces, f)
	return f
end

function Mesh:vertex(x, y, z)
	self.current.x = x
	self.current.y = y
	self.current.z = z
	
	table.insert(self.vertices, self.current)
	
	self.current = Vertex:new(0, 0, 0)
	
	return self.vertices[#self.vertices]
end

function Mesh:draw()
	local i, f
	for i = 1, #self.faces, 1 do
		f = self.faces[i]
		
		
		normal(f.normal.x, f.normal.y, f.normal.z)
		vertex(f.a.x, f.a.y, f.a.z)
		vertex(f.b.x, f.b.y, f.b.z)
		vertex(f.c.x, f.c.y, f.c.z)
	end	
end

--------------------------------------------------------------------------------

Music = {}
function Music.setup()
	Music.stream = loadMusicStream("data/3400-miles-below.mp3")
end

Gurrus = {}

function Gurrus.setup()
	local i, j, k, px, py, pz, numV
	local num_gurrus = 15
	local num_spikes = 20
	local radius = 45
	local radius_gurru
	local dist_radius = 150
	local mesh
	local ang
	
	Gurrus.meshes = {}
	
	for i = 1, num_gurrus, 1 do
		
		mesh = Mesh:new()
		numV = 1
		
		ang = i * math.pi * 2 / num_gurrus
		
		px = dist_radius * math.sin(ang)
		py = 0
		pz = dist_radius * math.cos(ang)
		
		radius_gurru = radius * (1 + 0.25*math.sin(ang*2))
		
		for j = 1, num_spikes, 1 do
			for k = 1, 3, 1 do
				
				mesh:vertex(
					px + radius_gurru*(math.random() - math.random()),
					py + radius_gurru*(math.random() - math.random()),
					pz + radius_gurru*(math.random() - math.random())
				)
			end
			
			mesh:face(mesh.vertices[numV], mesh.vertices[numV + 1], mesh.vertices[numV + 2])
			numV = numV + 3
		end
		
		table.insert(Gurrus.meshes, mesh)
	end
end

function Gurrus.draw(t, intensity)
	color(0, 1, 0, .15 * intensity)
	beginShape(SHAPE_TRIANGLES)
		for k, v in pairs(Gurrus.meshes) do
			v:draw()
		end
	endShape()
	
end

Ground = {}

function Ground.setup()
	local i, j, srcx, srcz, segx, segz, lenx, lenz, numx, numz
	local vertex, vertices, faces, numV, numF, px0, py0, pz0, px, py, pz
	
	-- size of the ground
	lenx = 500.0
	lenz = 500.0
	
	-- where does the ground begin
	srcx = -1 * lenx * 0.5
	srcz = -1 * lenz * 0.5
	
	-- number of segments
	numx = 30.0
	numz = 30.0
	
	-- length of each segment
	segx = lenx / numx
	segz = lenz / numz
	
	Ground.mesh = Mesh:new()
	numV = 1
	numF = 1
	px = 0
	py = 0
	pz = 0
	
	for j = 0, numz, 1 do
		
		pz0 = pz
		pz = srcz + j * segz
		
		for i = 0, numx, 1 do

			py0 = py
			py = math.random(0, 4)
		
			px0 = px
			px = srcx + i * segx
			
			if(i > 0 and j > 0) then

				-- Upper triangle
							
				Ground.mesh:vertex(px0, py0, pz0)
				Ground.mesh:vertex(px0, py, pz)
				Ground.mesh:vertex(px, py0, pz0)
				
				Ground.mesh:face(Ground.mesh.vertices[numV], Ground.mesh.vertices[numV + 1], Ground.mesh.vertices[numV + 2])
				
				numF = numF + 1
				numV = numV + 3
				
				-- Lower triangle
				
				Ground.mesh:vertex(px0, py, pz)
				Ground.mesh:vertex(px, py, pz)
				Ground.mesh:vertex(px, py0, pz0)
				
				Ground.mesh:face(Ground.mesh.vertices[numV], Ground.mesh.vertices[numV + 1], Ground.mesh.vertices[numV + 2])
			
				numF = numF + 1
				numV = numV + 3
				
			end
		end
	end
end

Rotobichos = {}
function Rotobichos.setup()
	local i, ang_step, num_legs, coords, v, radius, num_bichos, dist_radius
	
	coords = {}
	num_legs = 30
	ang_step = math.pi * 2.0 / num_legs
	radius = 5
	dist_radius = 70
	
	for i = 0, num_legs, 1 do
		v = Vertex:new()
		v.x = radius * math.sin(i * ang_step)
		v.y = radius * math.cos(i * ang_step)
		v.z = radius * math.cos(i * 4 * ang_step)
		
		table.insert(coords, v)
	end
	
	Rotobichos.coords = coords
	
	coords = {}
	
	num_bichos = 10
	
	for i = 0, num_bichos, 1 do
		v = Vertex:new()
		v.x = dist_radius * (math.random() - math.random())
		v.y = radius * 1.25 
		v.z = dist_radius * (math.random() - math.random())
		
		table.insert(coords, v)
	end
	
	Rotobichos.bichos_coords = coords
end

function Rotobichos.draw(t, intensity)
	local v, tmp_coords, bicho_coords, s
	
	blending(BLENDING_ALPHABLEND)
	color(0, 1, 0, 0.3 * intensity)
	
	for j = 1, #Rotobichos.bichos_coords, 1 do
	
		tmp_coords = {}
		s = math.pow(j, 2) * 0.75 + 1
		
		for i = 1, #Rotobichos.coords, 1 do
			v = Rotobichos.coords[i]
			bicho_coords = Rotobichos.bichos_coords[j]
			
			tmp_coords[i] = {}
			tmp_coords[i].x = v.x + bicho_coords.x
			tmp_coords[i].y = v.y + bicho_coords.y  + math.sin(t*0.001 + v.y + v.x + v.z)
			tmp_coords[i].z = v.z + bicho_coords.z
		end
		
		beginShape(SHAPE_LINES)
			for i = 1, #tmp_coords, 1 do
				v = tmp_coords[i]
				vertex(bicho_coords.x * s, bicho_coords.y * s, bicho_coords.z * s)
				vertex(v.x * s, v.y * s, v.z * s)
			end
		endShape()
		
		pointSize(4)
		beginShape(SHAPE_POINTS)
			for i = 1, #tmp_coords, 1 do
				v = tmp_coords[i]
				vertex(v.x * s, v.y * s, v.z * s)
			end
		endShape()
	
	end
	
	noBlending()

end

Plancton = {}
function Plancton.setup()
	local i, coords, num, radius, v
	
	coords = {}
	num = 650
	radius = 150
	
	for i = 0, num, 1 do
		v = {}
		v.x = radius * (math.random() - math.random())
		v.y = radius * math.random()
		v.z = radius * (math.random() - math.random())
		v.size = math.random(1, 3)
		
		table.insert(coords, v)
	end
	
	
	Plancton.coords = coords
	Plancton.t0 = 0
end

function Plancton.draw(t, intensity)
	local i, coord, tt, ttt, n, elapsed
	
		elapsed = t - Plancton.t0
		Plancton.t0 = t
		
		blending(BLENDING_ADDITIVE)
			color(0, 1, 0, 0.2 * intensity)
			tt = t * 0.001
			beginShape(SHAPE_TRIANGLES)
				for i = 1, #Plancton.coords, 1 do
					coord = Plancton.coords[i]
					ttt = tt + i
					
					vertex(coord.x, coord.y, coord.z)
					vertex(coord.x + coord.size*math.sin(ttt), coord.y, coord.z)
					vertex(coord.x, coord.y + coord.size, coord.z + coord.size*math.cos(ttt))
					coord.y = coord.y + 0.01 * elapsed 
					if(coord.y > 170) then
						Plancton.coords[i].y = math.random(-10, 0)
					end
				end
			endShape()
		noBlending()
end

Texts = {}
function Texts.setup()
	local i, j, line_width, text_height, point, escena, escena_coords, num, disp_x, disp_z
	
	escena = {
	"XXXXXXXXXX XXXXXXXXXX XXXXXXXXXX XXXXXXXXXX XXXXXXXXXX XXXXXXXXXX    XXXXXXXXXX XXXXXXXXXX XXXXXXXXXX",
	"XX      XX XX         XX         XX      XX XX      XX         XX    XX      XX XX         XX        ",
	"XXXXXXXXXX XXXXXXXXXX XX         XXXXXXXXXX XX      XX XXXXXXXXXX    XX      XX XX         XX     XXX",
	"XX                 XX XX         XX         XX      XX XX      XX    XX      XX XX         XX      XX",
	"XXXXXXXXXX XXXXXXXXXX XXXXXXXXXX XXXXXXXXXX XX      XX XXXXXXXXXX XX XXXXXXXXXX XX         XXXXXXXXXX",
	"                                                                                                     "
	}
	
	escena_coords = {}
	num = 8
	
	text_height = #escena
	disp_z = 0.1 / text_height
	
	for k, v in pairs(escena) do
		line_width = string.len(v)
		disp_x = 0.51 / line_width
		
		for i = 1, line_width, 1 do
			
			if(v:sub(i, i):match('X')) then
				for j = 0, num, 1 do
					
					point = {}
					
					point.dst_x = i * 1.0 / line_width * 1.0 + disp_x * (math.random() - math.random())
					point.dst_y = 1
					point.dst_z = k * 1.0 / text_height * 1.0 + disp_z * (math.random() - math.random())
					
					point.src_x = 0
					point.src_y = -0.5 * math.random() - 0.5*(j-1)
					point.src_z = 0
					
					table.insert(escena_coords, point)
				end
			end
		end
	end
	
	Texts.escena = { coords = escena_coords, width = escena[1]:len() * 2.1, height = #escena * 2.1 }
end

function draw_scene(t)
	local i, j, row, cx, cy, cz, lookx, looky, lookz, camera_fov, tt, tt2, v1, v2, v3, v4, e1, e2, radius
	local lx, ly, lz
	local mult = 0.00002
	local elapsed
	local escena_text_height = 200
	
	elapsed = t - global_t0
	global_t0 = t
	
	tt = t * mult - math.pi * 0.25 -- so that the text ends in the right place ;)
	tt2 = tt + math.pi*0.15
		
	camera_fov = 60
	
	---- start ----
	local camera_change_time = 153000
	
	if(t < camera_change_time) then
		radius = 200
		looky = 7
	else
		radius = 200 * math.max(0, NumberUtils.map(t, camera_change_time, 230000, 1, 0))
		looky = math.min(escena_text_height, 7 + escena_text_height * NumberUtils.normalize(t, camera_change_time, 230000))
	end
	
	-- Camera
	local sint, cost
	
	sint = math.sin(tt)
	cost = math.cos(tt)
	
	cx = radius * sint
	cz = radius * cost
	cy = 8 + 3 * math.sin(tt*20)
	
	lookx = 0
	lookz = 0
	
	-- Light
	local radius_light = radius - 20
	lx = radius_light * sint
	ly = cy + 2
	lz = radius_light * cost
	
	
	camera(cx, cy, cz,   lookx, looky, lookz,    0, 1, 0)
	perspective(camera_fov, SCREEN_WIDTH/SCREEN_HEIGHT*1.0, 1, 2000)

	local intensity = math.min(1, NumberUtils.map(t, 0, 30000, 0, 1))
	
	local light = 0
	lightEnabled(light, true)
	lightPosition(light, lx, ly, lz, 1)
	lightAmbient(light, 0.0, 0.0, 0.0, 1)
	lightDiffuse(light, 0, intensity, 0, 1)
	
	depthTest()
	
	fogMode(FOG_EXP)
	fogDensity(0.002)
	fogColor(0, 0, 0, 1)
	fogStartEnd(1, 1000)
	
	
	-- Ground
	colorMode(COLOR_FLAT)
	beginShape(SHAPE_TRIANGLES)
		Ground.mesh:draw()
	endShape()
	
	noBlending()

	-- Gurrus
	Gurrus.draw(t, intensity)
		
	noLights()
	
	-- Rotobichos
	Rotobichos.draw(t, intensity)

	-- plancton
	Plancton.draw(t, intensity)
	
	
	-- escena text
	local escena_text_start = 40000
	local escena_text_end = 200000
	if(t > escena_text_start) then
		local i, v, ox, oz, vx, vy, vz, dst, src
		
		ox = -0.5 * Texts.escena.width
		oz = -0.5 * Texts.escena.height
		
		dst = math.min(1, (t - escena_text_start) / (escena_text_end - escena_text_start))
		src = 1 - dst
		
		-- This is for the colour change from g to r
		local r = math.max(0, NumberUtils.normalize(t, 180000, escena_text_end))
		
		pointSize(3)
		blending(BLENDING_ADDITIVE)
		beginShape(SHAPE_POINTS)
			for i = 1, #Texts.escena.coords, 1 do
				v = Texts.escena.coords[i]
				
				vx =  - (ox + (v.src_x * src + v.dst_x * dst) * Texts.escena.width)
				vy = (v.src_y * src + v.dst_y * dst) * escena_text_height
				vz = oz + (v.src_z * src + v.dst_z * dst) * Texts.escena.height
				
				color(r, 1- r, 0, 0.1 + 0.5 * vy / escena_text_height)
				
				vertex(vx, vy, vz)
			
			end
		endShape()
		noBlending()
	end
	
	fogMode(FOG_NONE)
	
	noDepthTest()
	
	restoreProjection()
end

function draw(ticks)
	local time, i
	
	time = getMusicStreamTime(Music.stream)
		
	background(0, 0, 0, 1)
	
	draw_scene(time)

	if(time > 230000) then
		quit()
	end
	
end
