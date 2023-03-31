--print('hello world\n')
--print('Lua from event:', param)

if param == 'collision' then
	playsound('fx1')
elseif param == 'attack' then
	playsound('fx2')
end