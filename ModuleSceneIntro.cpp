#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(0.0f, 75.0f, 20.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	Object wall;
	wall.cube.Scale(0.5, 3, 10);
	wall.cube.SetRotation(90, vec3{ 0, 1, 0 });
	wall.cube.color = Orange;

	wall.pb_cube = App->physics->AddBody(wall.cube, 100000);
	wall.pb_cube->SetPos(0, 1.5, 15);
	circuit.add(wall);

	Object wall1;
	wall1.cube.Scale(0.5, 3, 3);
	wall1.cube.SetRotation(90, vec3{ 0, 1, 0 });
	wall1.cube.color = Orange;

	wall1.pb_cube = App->physics->AddBody(wall1.cube, 100);
	wall1.pb_cube->SetPos(3, 1.5, 0);

	Object sphera;
	sphera.sphere.radius = 5.0f;
	sphera.sphere.color = Orange;

	sphera.pb_cube = App->physics->AddBody(sphera.sphere, 1000);
	sphera.pb_cube->SetPos(0, 10, -10);


	circuit.add(wall1);
	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	circuit.clear();
	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

	p2List_item<Object>* item = circuit.getFirst();

	while (item != NULL) {

		item->data.pb_cube->GetTransform(item->data.cube.transform.M);
		item->data.cube.Render();
		item = item->next;

	}
	

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

