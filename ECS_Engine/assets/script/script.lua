print('hello world\n')
print('Lua from event:', param)

if param == 'collision' then
	playsound('FX1')
elseif param == 'attack' then
	playsound('FX2')
end