Animatie
{
	nume
	begin
	end
	speed
	currentTime
	textura
	loop
}

AnimationMgr
{
	animatii;
	animatieCurenta;

	Play(numeAnimatie);
	Stop();
	Pause();
	SetFrame();

	Update(dt);
	
}

