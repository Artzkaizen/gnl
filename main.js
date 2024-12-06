const sectionWrapper = document.getElementById("module-1748");
if(sectionWrapper) sectionWrapper.style = "border: none"

const activities  = Object.values(@@DATASET@@);

for (const activity of activities) {
  const activityLink = document.getElementById(activity.idnumber);
	if (!activityLink) continue; // Skip if no element is found for the activity idnumber

	switch (activity.idnumber) {
		case "menu_attendance":
			activityLink.href = `/mod/attendance/view.php?id=${activity.id}`;
			break;

		case "menu_dailylogs":
			activityLink.href = `/mod/dailylogs/view.php?id=${activity.id}`;
			break;

		case "menu_announcements":
			activityLink.href = `/mod/forum/view.php?id=${activity.id}`;
			break;

		case "menu_forum":
			activityLink.href = `/mod/forum/view.php?id=${activity.id}`;
			break;

		case "menu_glossary":
			activityLink.href = `/mod/glossary/view.php?id=${activity.id}`;
			break;

		case "menu_legal_references":
			activityLink.href = `/mod/page/view.php?id=${activity.id}`;
			break;

		case "menu_handbook":
			activityLink.href = `/mod/page/view.php?id=${activity.id}`;
			break;

		case "menu_tasks_exams":
			activityLink.href = `/mod/page/view.php?id=${activity.id}`;
			break;
		case "menu_virtual_room":
			activityLink.href = `/mod/bigbluebuttonbn/view.php?id=${activity.id}`;
			break;
                case "menu_certificate":
			activityLink.href = `/mod/coursecertificate/view.php?id=${activity.id}`;
			break;

		default:
			break;
	}
}

